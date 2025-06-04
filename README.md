# Minishell

A compact recreation of the bash shell, implementing key concepts such as file descriptors, process management, and command parsing. This 42 School project demonstrates systems programming fundamentals through building a functional UNIX shell from scratch.

![Demo](https://img.shields.io/badge/42-Project-brightgreen)
![Language](https://img.shields.io/badge/Language-C-darkgrey)

## 🐚 About

Minishell is a simplified implementation of bash that handles essential shell operations including command execution, pipes, redirections, and built-in commands. Built entirely in C with strict memory management and following the 42 coding standards.

## ✨ Features

- **Interactive Prompt**: Command-line interface with history support
- **Command Execution**: System executables and local programs
- **Built-in Commands**: Essential shell commands implemented natively
- **Pipes & Redirections**: Full I/O redirection and command chaining
- **Environment Variables**: Variable expansion and manipulation
- **Signal Handling**: Proper Ctrl+C, Ctrl+D, and Ctrl+\ behavior
- **Quote Parsing**: Single and double quote handling
- **Error Management**: Comprehensive error handling and exit codes

## 🛠️ Supported Features

### Built-in Commands
```
| Command | Description                  | Options                 |
|---------|------------------------------|-------------------------|
| `echo`  | Display text                 | `-n` (no newline)       |
| `cd`    | Change directory             | Relative/absolute paths |
| `pwd`   | Print working directory      | None                    |
| `export`| Set environment variables    | Variable assignment     |
| `unset` | Remove environment variables | Variable names          |
| `env`   | Display environment          | None                    |
| `exit`  | Exit shell                   | Optional exit code      |
```
### Operators & Redirections
```
| Oper | Function                     | Example                            |
|------|------------------------------|------------------------------------|
| `|`  | Pipe output to next command  | `ls | grep .c`                     |
| `>`  | Redirect output              | `echo "text" > file.txt`           |
| `>>` | Append output                | `date >> log.txt`                  |
| `<`  | Redirect input               | `sort < data.txt `                 |
| `<<` | Here document                | `cat << EOF`                       |
| `&&` | Execute if previous succeeds | `make && ./program`                |
| `||` | Execute if previous fails    | `test -f file || echo "not found"` |
| `&`  | Run command in background    | `sleep 10 &`                       |
minishell$ cat  processed.txt
minishell$ ls >> file_list.txt
```

### Environment Variables
- **Variable Expansion**: `$HOME`, `$USER`, `$PATH`
- **Exit Status**: `$?` expands to last command's exit code
- **Custom Variables**: Set and use custom environment variables
- **Quote Handling**: Different expansion behavior in single vs double quotes
```
minishell$ export MY_VAR="test value"
minishell$ echo $MY_VAR
test value

minishell$ echo "Exit code: $?"
Exit code: 0
```

### Signal Handling

- **Ctrl+C (SIGINT)**: 
  - If foreground process running: send SIGINT to child
  - If no foreground process: display new prompt
- **Ctrl+D**: Exit minishell cleanly
- **Ctrl+Z (SIGTSTP)**: Stop foreground process and show PID
- **Ctrl+\**: No action (ignored)

### Here Documents
```
minishell$ cat  This is a here document
> Multiple lines supported
> EOF
This is a here document
Multiple lines supported
```

## 🏗️ Project Structure

```
minishell/
├── src/                    # Source files
│   ├── main.c             # Program entry point
│   ├── parser/            # Command parsing logic
│   │   ├── lexer.c        # Tokenization
│   │   ├── parser.c       # Syntax analysis
│   │   └── expander.c     # Variable expansion
│   ├── executor/          # Command execution
│   │   ├── executor.c     # Main execution logic
│   │   ├── pipes.c        # Pipe handling
│   │   └── redirections.c # I/O redirection
│   ├── builtins/          # Built-in commands
│   │   ├── echo.c         # Echo implementation
│   │   ├── cd.c           # Directory change
│   │   ├── pwd.c          # Working directory
│   │   ├── export.c       # Environment export
│   │   ├── unset.c        # Variable removal
│   │   ├── env.c          # Environment display
│   │   └── exit.c         # Shell exit
│   ├── signals/           # Signal handling
│   └── utils/             # Utility functions
├── includes/
│   └── minishell.h        # Header file
├── Makefile              # Build configuration
└── README.md
```

## 🔧 Technical Implementation

### Core Components

**Lexical Analysis**: Tokenizes input into meaningful components (commands, operators, arguments)

**Syntax Parsing**: Builds command structures and validates syntax

**Variable Expansion**: Processes environment variables and special parameters

**Process Management**: Handles fork/exec for command execution

**File Descriptor Management**: Manages pipes and redirections efficiently

**Memory Management**: Ensures zero memory leaks with proper cleanup

### Key Algorithms

**Command Pipeline**: Implements pipe chains with proper file descriptor handling

**Quote Processing**: Handles nested quotes and escape sequences

**Path Resolution**: Searches PATH environment variable for executables

**Signal Safety**: Implements async-signal-safe signal handlers

## 🧪 Testing

### Manual Testing
```
# Test basic commands
./minishell
minishell$ echo test
minishell$ pwd
minishell$ cd ..

# Test pipes and redirections
minishell$ ls | wc -l
minishell$ echo "test" > file.txt
minishell$ cat < file.txt

# Test environment variables
minishell$ export TEST=value
minishell$ echo $TEST
minishell$ unset TEST
```

### Edge Cases
- Empty commands and multiple spaces
- Unclosed quotes and syntax errors
- Invalid file permissions
- Signal interruption during execution
- Large command pipelines

## 🚫 Limitations

Minishell does **not** support:
- Wildcards (`*`, `?`, `[]`)
- Command substitution (`` `command` `` or `$(command)`)
- Logical operators (`&&`, `||`)
- Command separators (`;`)
- Backslash escaping (`\`)
- Job control and background processes (`&`)

## 🤝 Contributing

This is a 42 School project, but contributions for educational purposes are welcome:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -m 'Add improvement'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request

## 📚 Learning Resources

- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [POSIX Shell Specification](https://pubs.opengroup.org/onlinepubs/9699919799/)
- [Advanced Programming in UNIX Environment](https://www.apue.com/)
- [Systems Programming Book](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/)

## 🎯 42 School Requirements

- **Norm Compliance**: Follows 42 coding standards
- **Memory Management**: Zero memory leaks (verified with Valgrind)
- **Error Handling**: Comprehensive error management
- **Function Restrictions**: Limited to approved system calls
- **Global Variables**: Minimal global state usage

## 📄 License

This project is part of the 42 School curriculum. Use for educational purposes only.

## 👤 Author

**Maksym Voloshyn**
- GitHub: [@voloshynm](https://github.com/voloshynm)
- 42 Login: mvoloshyn
- Email: mvoloshy@student.42luxembourg.lu

**Sergio Filipe**
- GitHub: [@](https://github.com/)
- 42 Login: sandre-a
- Email: sandre-a@student.42luxembourg.lu

## 🙏 Acknowledgments

- **42 School** - Project specification and learning framework
- **GNU Bash Team** - Reference implementation and documentation
- **UNIX Pioneers** - Shell design principles and philosophy
- **Fellow 42 Students** - Collaboration and peer learning

---

*"Understanding shells means understanding UNIX" - Building minishell teaches the fundamentals of systems programming*

**Keywords**: `c-programming` `unix-shell` `42-school` `systems-programming` `bash` `shell` `pipes` `redirections` `process-management`
