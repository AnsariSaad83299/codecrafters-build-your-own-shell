# Build Your Own Shell in C

This is a Unix-like shell implemented in **C** as part of the **CodeCrafters.io** challenge. The project is aimed at learning low-level programming, process management, and command parsing from scratch.

**Work in progress.**

---

## Features Implemented

- **Command parsing and tokenization**  
  Handles spaces, single quotes `'`, double quotes `"`, and backslash escaping `\`.

- **Built-in commands**  
  - `cd` – change directory  
  - `pwd` – print current working directory  
  - `echo` – print arguments  
  - `type` – check if command is built-in or external  

- **External command execution**  
  Uses `fork()` and `execv()` to run external programs.

- **Output redirection**  
  Supports `>` and `1>` to redirect standard output to files.

---

## Learning Outcomes

- Understanding how shells parse and execute commands  
- Managing processes and file descriptors in C  
- Handling complex quoting, escaping, and redirection logic  
- Appreciating the hidden complexity in tools we often take for granted 
