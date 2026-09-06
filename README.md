# Custom UNIX Shell (v2.0)

A lightweight, robust POSIX-compliant UNIX shell written from scratch in C. Version 2.0 introduces an Abstract Syntax Tree (AST) engine capable of deterministic execution for complex command pipelines, conditional short-circuit branching, and simultaneous file stream redirections.

---

## Key Features

- **Single-Pass Left-Associative AST Engine:** Parses recursive execution trees with arbitrary chaining of pipelines and logical operators.
- **IPC Pipelines (`|`):** Supports multi-stage piping with bidirectional process chaining and explicit file descriptor lifecycle management.
- **Logical Branching (`&&`, `||`):** Short-circuits command execution dynamically based on POSIX exit codes (`0` vs. non-zero).
- **Stream Redirections (`<`, `>`, `>>`):** Supports input redirection, output truncation, and append modes simultaneously per command block without race conditions.
- **Robust Process Management:** Clean `fork()`, `execvp()`, and `waitpid()` process lifecycles with `WEXITSTATUS` status propagation.
- **Signal Handling:** Isolates `SIGINT` (`Ctrl+C`) to terminate active foreground child processes without killing the parent shell session.
- **Zero-Leak Tree Teardown:** Post-order recursive deallocation strictly validated with AddressSanitizer (ASan) to ensure zero memory corruption or use-after-free bugs.

---

## Architecture Overview

Instead of using flat, sequential token buffers, this shell constructs an in-memory Abstract Syntax Tree using a deferred pointer socket mechanism.

### Node Types

```
             [ Tree Node ]
              /         \
    [ NODE_CMD ]       [ Operator Node ]
    - tokens[]         - left child
    - file_in          - right child
    - file_out         - type: PIPE / AND / OR
    - append_file
```

### Execution Traversal

The AST executes recursively using **left-associative post-order/in-order traversal**:

1. **Logical Nodes (`&&`, `||`)**: Evaluates `left` first. Based on the return exit code:
   - `&&` executes `right` only if `status == 0`.
   - `||` executes `right` only if `status != 0`.
   - Returns the exit status of the final executed command.
2. **Pipes (`|`)**: Allocates an IPC channel via `pipe(2)`, wires the left child's `STDOUT_FILENO` to `fd[1]`, wires the right child's `STDIN_FILENO` to `fd[0]`, and ensures all unused descriptor ends are closed across parent and children to prevent deadlocks.
3. **Command Leaves (`NODE_CMD`)**: Opens explicit input/output files and replaces file descriptors using `dup2(2)` before handing execution to `execvp(3)`.

---

## File Structure

```text
.
├── Makefile         # Build rules with ASan and standard flags
├── buildins.c       # Builtin implementations (cd, exit, etc.)
├── buildins.h       # Function pointer prototypes for builtins
├── function.c       # Low-level AST execution & fork/dup2 logic
├── function.h       # Execution interface headers
├── getline.c        # Custom line reading and stream buffering
├── hash.c           # Fast command hashing and lookup tables
├── hash.h           # Hash table definitions
├── helper.c         # String tokenization and utility helpers
├── helper.h         # Helper definitions
├── parser.c         # Recursive-descent & deferred pointer AST builder
├── parser.h         # AST construction declarations
├── shared.h         # Shared defines, error codes, and macros
├── shell.c          # REPL main loop and signal handler setup
└── struct.h         # Tree and token struct definitions
```

---

## Building and Running

### Prerequisites

- GCC or Clang
- POSIX-compliant Linux environment (Fedora, Ubuntu, Debian, etc.)
- GNU Make

### Compilation

Build with standard optimizations:
```bash
make
```

Build with **AddressSanitizer (ASan)** enabled for memory debugging:
```bash
make CFLAGS="-Wall -Wextra -g -fsanitize=address"
```

### Running the Shell

Launch the interactive prompt:
```bash
./shell
```

---

## Verified Test Scenarios

### 1. Multi-Stage Pipeline Execution
```bash
ls -1 | wc -l
cat /etc/passwd | head -n 5 | wc -l
```
*Validates descriptor cleanup; pipelines terminate instantly without hung readers.*

### 2. Simultaneous Input and Output Redirection
```bash
cat < /etc/hosts > test_hosts.txt && cat test_hosts.txt
```
*Validates that an individual command node applies both `STDIN` and `STDOUT` redirection seamlessly.*

### 3. Redirection Error Handling
```bash
cat < nonexistent_file_xyz.txt
```
*Ensures `open()` failures print descriptive errors and exit the child safely without stalling the shell.*

### 4. Logical Operators and Short-Circuiting
```bash
true && echo AND_PASSED || echo AND_FAILED
false || echo OR_PASSED && echo CHAIN_PASSED
```
*Validates conditional branching based on POSIX exit codes.*

### 5. File Descriptor Leak Verification
```bash
ls | cat | wc -l && ls /proc/self/fd
```
*Confirms no lingering pipes or file handles exist across cycles.*

---

## Memory Safety

All AST memory is reclaimed post-execution using a defensive post-order deallocation function:

```c
int free_node(tree_node *head) {
    if (!head) return 0;
    if (head->type != NODE_CMD) {
        free_node(head->operator_node.left);
        free_node(head->operator_node.right);
    }
    free(head);
    return 1;
}
```

The shell runs completely leak-free and passes AddressSanitizer validations across all execution cycles.
