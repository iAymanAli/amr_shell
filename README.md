<h1 style="border-bottom: none; border: none;">amr shell 👨‍💻</h1>

# Introduction
Hello 👋

"**amr**" is a custom shell that I built from scratch. I built it for the primary reason of learning more about systems and how things work under the hood. As a side-effect, I learned more about C language, Unix, shells, and some programming skills.

I called it "**amr**" because it means "command" in Arabic.

I followed the behavior and rules of the **bash** shell which is considered the standard nowadays. Also, this shell only works for Linux in its current version, hopefully I will expand it to work for MacOS and Windows in the future.


# How to install and use

### Prerequisites
Before building `amr`, ensure you have a C compiler, `make`, and the `readline` development libraries installed.

### Steps
1. Clone the repository into your own machine.
```bash
git clone https://github.com/iAymanAli/amr_shell.git
```

2. Go to the root of the project directory.
```bash
cd amr_shell
```

3. Make sure you have "**make**" in your machine. Install it if it does not exist.
```bash
make --version
```

4. Compile the code.
```bash
make amr
```

5. Run amr shell.
```bash
make run
```

6. Try it and Enjoy !


# Tech stack & tools
**Language**: C

**Libraries**: GNU readline

**Tools**: GNU make


# Features
1. It has autocomplete for commands, directories, and file names.

2. It can handle backslash, single-quotes, and double-quotes in the user input.

3. It has history that you can access with UP and DOWN arrows.

4. Built-in commands.
    
    a. `echo`
    
    b. `type`

    c. `cd`

    d. `pwd`

    e. `complete`

    f. `exit`

5. It has the ability to execute commands that exist in the PATH directories.

6. It can redirect output via `1>`, `>`, `2>`, `1>>`, `>>`, and `2>>`.

7. It can perform piping with an unlimited number of pipes.


# Code structure
* `main.c`: contains the code for taking user input, tokenizing it, and conditionals to execute the correct command. Also, piping is being handled in this file.

* `tokenizers.c`: contains the code for parsing and tokenizing user input.

* `utils.c`: contains functions that are necessary for autocompletion and command handlers.

* `autocompletion_handlers.c`: contains functions that handle both the "complete" built-in command and autocompletion for the readline library.

* `cmd_handlers.c`: contains functions that handle executing built-in commands and commands from PATH.


# What I learned
In this section I will briefly list the things I learned during the process of implementing this project, and I will provide some resources that you can access if you are interested in learning these stuff.

1. How to tokenize user input and handle single and double quotes, and how state-machine tokenizers work

    Article: [Article will be published soon]

2. How to get and set environment variables
    
    Article: (Read Approach 3) - [Ways to get and set environment variables in C](https://dev.to/namantam1/ways-to-get-and-set-environment-variables-in-c-200m)

3. System call functions: `fork` and `exec` functions family

    Article: [Building a Shell in C using fork and Process Management](https://valerius-petrini.vercel.app/blog/2025-06-29-fork-linux)

    YouTube Playlist: [Unix Processes in C](https://youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&si=x3KY4HqsD45yAzRu)

4. System call functions: `chdir` and `getcwd`

    Article: (chdir manual) - [chdir(2) - Linux manual page](https://man7.org/linux/man-pages/man2/chdir.2.html)

    Article: (getcwd manual) - [getcwd(3) - Linux manual page](https://man7.org/linux/man-pages/man3/getcwd.3.html)

5. readline library, its usage, and its features

    Article: [Tab completion in GNU Readline](https://thoughtbot.com/blog/tab-completion-in-gnu-readline)

6. How to redirect `stdout` and `stderr` to a file

    Article: [C, UNIX: How to redirect ‘stdout’ to a file from a C code?](https://community.unix.com/t/c-unix-how-to-redirect-stdout-to-a-file-from-a-c-code/362998)

7. How to open a directory and read its content

    Article: [Exploring Directory Operations: opendir, readdir, and closedir System Calls](https://medium.com/@noransaber685/exploring-directory-operations-opendir-readdir-and-closedir-system-calls-a8fb1b6e67bb)

8. Piping and how can commands communicate with each other

    Book: (Read Chapter 5 - Pipes) - [Beej’s Guide to Interprocess Communication](https://beej.us/guide/bgipc/)

    YouTube Playlist: [Unix Processes in C](https://youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&si=x3KY4HqsD45yAzRu)


# Future improvements
* Support for double-quotes autocompletion and autocompletion for file names that contain spaces

* Support for shell variables.

* Support for aliases

* Ability to run the shell in a separate window

* Desktop file for the shell

* Versions for MacOS and Windows

* Ability to download amr shell with package managers


# Contributing Guidelines
I welcome contributions! To maintain code quality and stability, please ensure your pull request meets the following testing and documentation requirements before submitting:

* **Comprehensive Testing**: You must test all new code against all possible user cases and edge cases. Ensure your implementation gracefully handles any arbitrary or invalid user input without crashing.

* **Test Documentation File**: Create or update a .md file (e.g., TESTING.md or inside your PR description) that lists every test case conducted, the input parameters used, and the observed results.

* **Explicit Description of Changes**: Clearly document the exact scope of your work. Detail all new features added, existing functionality modified, or performance improvements made to the codebase.


# Conclusion
I hope you had sufficient information reading this README, and I also hope that you enjoyed using amr shell.

Thank you for your time. Have a nice day 👋