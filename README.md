
![THE_GATES_OF_SHELL (1)](https://github.com/Mk-0-wan/simple_shell/assets/114664618/f08a06bf-085b-4ac9-88de-b6246d19916f)

# 🐚 Simple shell 🐚

Basically this is a simple implementaion of [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson) shell, who among others at Bell Labs (formerly AT&T Bell Telephone Laboratories) designed and implemented The original Unix operating system.


# What's the shell 🤔?

A shell is a user interface for accessing an operating system's services. It can be command-line-based or have a graphical user interface (GUI). In the context of operating systems like Unix, Linux, and others, a shell typically refers to a command-line interface where users interact with the system by typing commands.

## How does it work ☕ ?

1. **_Command Interpretation_**: The shell interprets user commands and translates them into a format that the operating system can understand and execute.

2. **_Scripting_**: Shells often support scripting languages, allowing users to write scripts (sequences of commands) to automate tasks.

3. **_File Manipulation_**: Users can navigate the file system, create, delete, and manipulate files and directories through shell commands.

4. **_Environment Customization_**: Users can customize their shell environment, setting variables, configuring aliases, and defining functions.

5. **_Input/Output Redirection_**: Users can redirect the input and output of commands, enabling powerful data manipulation and processing.

5. **_Job Control_**: Shells allow users to run multiple processes simultaneously and manage their execution.

# Installation 🛠️?
- Before installation make sure you have the following installed on your local machine
    - GNU Compiler Collection Version 13.2.[ Here](https://www.scaler.com/topics/c/c-compiler-for-windows/)
    - Debian Based Linux OS.(Arch, Ubuntu or Manjaro) [Here](https://wiki.archlinux.org/title/installation_guide)
    - Git CLI. [Here](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)
- Once you have all those installed let's move on to the next step. Run this on your terminal
    ```bash
    git clone https://github.com/Mk-0-wan/simple_shell && cd simple_shell
    ```
- Compile the file with the following command
    ```bash
    gcc -Wall -Werror -Wextra -pedantic -Wunused -std=gnu89 *.c main.h -o Sshell
    ```
# Running the prorgram 🚀
- After compilation do this
    ```bash
    ./Sshell
    ```
- Here are some of the Demo of what you can do.
<!--TODO-->
