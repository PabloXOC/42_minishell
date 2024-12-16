# 42 Minishell

Minishell is a small yet powerful custom shell that replicates key functionalities of traditional Unix shells like Bash. It allows users to execute commands, manage files and processes, and interact with the system through an intuitive and responsive command-line interface.  

With built-in support for essential shell features like pipes, redirection, and environment variable management, Minishell provides a streamlined and efficient user experience while adhering to the expected behavior of a modern shell.

## Features

### Core Functionality
- **Command Execution**:
  - Executes commands based on the `PATH` variable or via relative/absolute paths.
  - Supports built-in shell commands.
- **Interactive Prompt**:
  - Displays a prompt while waiting for user input.
  - Provides command history functionality.
- **Quoting**:
  - Single quotes (`'`) prevent interpretation of metacharacters.
  - Double quotes (`"`) prevent interpretation of metacharacters except `$`.
- **Command Separator**:
  - Support for the semicolon (`;`) to execute multiple commands sequentially within a single input line.

### Input/Output Handling
- **Redirections**:
  - `<` Redirects input.
  - `>` Redirects output.
  - `<<` Here-documents: Reads input until a specified delimiter is encountered.
  - `>>` Appends output.
- **Pipes**:
  - Supports pipelines (`|`), connecting the output of one command to the input of another.

### Environment Variable Management
- Expands variables prefixed with `$`.
- `$?` expands to the exit status of the most recently executed command.

### Signal Handling
- Properly handles `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`:
  - `Ctrl-C`: Interrupts the current process and displays a new prompt.
  - `Ctrl-D`: Exits the shell.
  - `Ctrl-\`: Does nothing in interactive mode, exits if used while in a command.

### Built-in Commands
Commands that are implemented directly within the shell itself, as opposed to being executed by launching an external program. They do not depend on the PATH environment variable.
- **`echo`**: Prints text to the terminal, with support for the `-n` flag.
- **`cd`**: Changes the current working directory.
- **`pwd`**: Displays the current working directory.
- **`export`**: Sets environment variables.
- **`unset`**: Unsets environment variables.
- **`env`**: Prints environment variables.
- **`exit`**: Exits the shell.


## Compilation and Execution

### Compilation
Use the provided `Makefile` to compile the project:
```bash
make
```
This will generate the `minishell` executable.

### Execution
Run the shell interactively:
```bash
./minishell
```

### Cleaning Up
Use the following commands for cleanup:

- `make clean`: Remove object files.
- `make fclean`: Remove object files and the compiled executable.
- `make re`: Rebuild the project from scratch.

