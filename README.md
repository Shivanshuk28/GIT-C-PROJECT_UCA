
---

# Git Implementation (`Trackit`)

`Trackit` is a lightweight, Git-like version control system implemented in C. It provides basic functionality for tracking file changes, committing versions, and managing a simple index.

## Table of Contents

- [Git Implementation (`Trackit`)](#git-implementation-trackit)
  - [Table of Contents](#table-of-contents)
  - [Descriptiom](#description)
  - [Features](#features)
  - [Installation](#installation)
    - [Prerequisites](#prerequisites)
    - [Steps](#steps)
  - [Usage](#usage)
  - [Directory Structure](#directory-structure)
  - [Built-in Commands](#built-in-commands)

## Description

`Trackit` is a simple version control system that mimics some fundamental features of Git. It allows users to track changes to files, commit versions with messages, and manage a basic index of file versions. This project is implemented in C and demonstrates how to build a basic version control system from scratch.

## Features

Initialize a repository with trackit init
- **Built-in Commands**: Includes built-in commands like `cd`, `help`, and `exit`.
- **Custom Command Parsing**: Supports basic command parsing and argument handling.
- **Error Handling**: Provides error messages for invalid commands and improper usage.

## Installation

### Prerequisites

- GCC (GNU Compiler Collection) or any compatible C compiler.
- Make (build automation tool).
- Unix-like operating system (Linux, macOS, etc.).

### Steps

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/ShivamBajpai04/C-Project.git
    cd C-Project
    ```

2. **Build the Project**:
    Run the provided script to build and run the shell.
    ```bash
    ./run.sh
    ```

This script will compile the code and run the shell executable.

## Usage

Once the shell is running, you will see a prompt (`>`). You can type commands and hit Enter to execute them. The shell will continue running until you type `exit`.

Example:
```sh
> ls -l
> cd /path/to/directory
> help
> exit
```

## Directory Structure

```plaintext
proj/
├── bin/                # Compiled binary files
│   └── proj            # The proj shell executable
├── include/            # Header files
│   └── proj.h          # Function declarations and macros
├── obj/                # Object files
│   ├── builtins.o
│   ├── execute.o
│   ├── proj.o
│   └── utils.o
├── src/                # Source files
│   ├── builtins.c      # Built-in command implementations
│   ├── execute.c       # Command execution logic
│   ├── proj.c          # Main entry point
│   └── utils.c         # Utility functions
├── Makefile            # Build configuration
└── README.md           # Project documentation (this file)
```

## Built-in Commands

The `proj` shell includes the following built-in commands:

- **`cd [directory]`**: Change the current directory to `[directory]`. If no directory is provided, an error is displayed.
- **`help`**: Display information about the shell and the available built-in commands.
- **`exit`**: Exit the shell.

If a command is not recognized as a built-in command, `proj` will attempt to execute it as an external program.

---