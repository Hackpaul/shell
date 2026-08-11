# Custom C Unix Shell

A lightweight, modular Unix command-line interpreter written in **C**. This project explores operating system fundamentals, low-level process creation, signal handling, and text parsing.

---

## Features

* **Interactive REPL Loop:** Continuously reads, parses, and executes commands.
* **Process Execution:** Launches external binaries (`ls`, `python3`, `nvim`, `man`, etc.) using `fork()`, `execvp()`, and `waitpid()`.
* **Built-in Commands:**
  * `cd <dir>` — Changes current working directory (handles `$HOME` by default).
  * `exit` — Cleanly exits the shell loop.
* **Signal Handling:**
  * Ignores `SIGINT` (`Ctrl+C`) at the prompt without crashing the main shell loop.
  * Intercepts `SIGTSTP` (`Ctrl+Z`) and `SIGQUIT` (`Ctrl+\`).
  * Restores default signal behavior inside child processes so running programs can still be interrupted.
* **Modular Architecture:** Clean division of responsibilities across separate C source files.

---

## File Structure

```text
.
├── shell.c         # Entry point and main REPL loop
├── getline.c       # Custom line reader using system getline()
├── parser.c        # Tokenizer / String splitter
├── pid_handler.c   # Process creation logic (fork/exec/wait)
├── builtins.c      # Shell built-in command handlers (cd, exit)
├── shared.h        # Struct definitions and shared function declarations
└── Makefile        # Build rules for compilation

Building and Running
Prerequisites

    A Unix-like operating system (Linux, macOS, or WSL).

    gcc compiler and make.

Compilation

Build the shell binary using the included Makefile:
        
      1. build :  make
      2. run : ./shell

Example : 
 
user@pc$ ls -la
user@pc$ mkdir test_dir
user@pc$ cd test_dir
user@pc$ pwd
/home/user/project/shell/test_dir
user@pc$ python3
>>> exit()
user@pc$ cd ..
user@pc$ exit


Future Roadmap

    [ ] Custom State-Machine Tokenizer: Character-by-character scanner to support quotes ("hello world") and operators without requiring spaces.

    [ ] Abstract Syntax Tree (AST) Parser: Tree-based representation for complex command chains.

    [ ] I/O Redirection: Supporting standard input/output redirection (<, >).

    [ ] Piping: Connecting processes using pipe() (cmd1 | cmd2).
