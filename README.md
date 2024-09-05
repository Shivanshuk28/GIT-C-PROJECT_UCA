
---

# Git Implementation (`Trackit`)

`Trackit` is a lightweight, Git-like version control system implemented in C. It provides basic functionality for tracking file changes, committing versions, and managing a simple index, locally.

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

- Initialize a repository with `**trackit**`
- Add files to the Staging area with `**git add <file>**`
- Commit changes with a message using `**git commit -m "message"**`
- Shows status of the driectory using `**git status**`
- Can view all commits history in `**log file**`


## Installation

### Prerequisites

- GCC (GNU Compiler Collection) or any compatible C compiler.
- Make (build automation tool).
- Unix-like operating system (Linux, macOS, etc.).

### Steps

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/Shivanshuk28/GIT-C-PROJECT_UCA.git
    cd GIT_IMPLEMENTATION 
    ```

2. **Build the Project**:
    ```bash
    ./run.sh
    ```

    This script will compile the code and run the shell executable.

## Usage

Once the program is running, you will see **Enter command:** option.You can type commands and hit Enter to execute them.The interface/shell will continue running until you type exit.


Example:
1  **Initialize a Repository**
  ```sh
  Enter command:trackit
  ```
  This command creates a .trackit directory in your current working directory.

2  **Add Files to the Index:**
  ```sh
  Enter command:git add "name_of_file"
  ```
  This command adds the specified file to the index.

3 **Git status to show track of files:**
  ```sh
  Enter command:git status
  ```

4 **Commit Changes:**
  ```sh
  Enter command:git commit -m "message"
  ```
  This command creates a commit with the specified message. The commit ID is generated based on the SHA-1 hash of the index file.





## Directory Structure

```plaintext
── GIT_IMPLEMENTATION/            
    ├── .vscode/
    ├── include/              #Directory with all necessary header files
    │   ├── blob.h
    │   ├── commit.h
    │   ├── git_status.h
    │   ├── index.h
    │   └── init.h
    ├── outputfiles/          #Output files from src files
    │   ├── blob.o
    │   ├── commit.o
    │   ├── git_status.o
    │   ├── index.o
    │   └── init_git.o
    ├── src/                  #Src directory where all definitions are written    
    │   ├── blob.c
    │   ├── commit.c
    │   ├── git_status.c
    │   ├── index.c
    │   └── init_git.c
    ├── main.c                #Entry point to the whole program
    ├── my_program            #File created after running script file
    ├── README.md
    ├── run.sh                #Script file containing all execution steps
    ├── test1.txt             #Random files to test on
    ├── test2.txt
    ├── test3.txt
    └── test4.txt
```

- **`include/`**: Contains header files defining the structures and function prototypes.
- **`src/`**: Contains the source code files implementing the functionality.
- **`run.sh`**: Contains instructions for running the project.
- **`README.md`**: This file, providing documentation for the project.

## Screenshots

- **A simple illustration of how will our git and git commands will look like:**

  [![Screenshot-2024-09-06-023437.png](https://i.postimg.cc/65L0X4dn/Screenshot-2024-09-06-023437.png)](https://postimg.cc/SJR8Ls1x)


---