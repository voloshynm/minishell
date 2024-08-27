# Minishell

A compact recreation of the bash shell, applying key concepts such as file descriptors and process management.

## Table of Contents

- [Project Overview](#project-overview)
- [Understanding Bash](#understanding-bash)
- [Project Structure](#project-structure)
  - [Lexer](#lexer)
  - [Parser](#parser)
  - [Builtins](#builtins)
  - [Executor](#executor)
  - [Expander](#expander)
  - [Heredoc](#heredoc)
  - [Handling Commands](#handling-commands)
    - [Single Command](#single-command)
    - [Multiple Commands](#multiple-commands)
  - [Reset](#reset)
- [Key Takeaways](#key-takeaways)
- [Useful Resources](#useful-resources)

## Project Overview

This project involved creating a miniature version of the bash shell, which was both a challenging and extensive endeavor. It required an in-depth understanding of how bash processes commands, and I implemented several key features:

- Command prompt display for new input.
- Command history functionality.
- Execution of binaries (via PATH or absolute paths).
- Handling of quotes (single and double) similar to bash.
- Implementation of I/O redirections:
  - `<` for input redirection.
  - `>` for output redirection.
  - `<<` for heredocs (without affecting history).
  - `>>` for output redirection in append mode.
- Pipe `|` support for chaining commands.
- Environment variable handling.
- Support for `$?` to check the last command's exit status.
- Proper handling of signals like `ctrl-C`, `ctrl-D`, and `ctrl-\` in a bash-like manner.
- Reimplementation of several bash builtins:
  - `echo` with `-n` option.
  - `cd` for changing directories.
  - `pwd` to print the current directory.
  - `export` to set environment variables.
  - `unset` to unset environment variables.
  - `env` to print environment variables.
  - `exit` to terminate the shell.

Features like `&&`, `||`, and wildcard expansions were not required for this project.

## Understanding Bash

The shell serves as a bridge between the user and the operating system's services. Bash is one of the most widely used shells. For this project, I needed a deep understanding of bash's internals, which I divided into four main stages: lexer, parser, expander, and executor. 

## Project Structure

### Lexer

The lexer, or tokenizer, breaks down the input line into individual tokens. It reads the input line word by word, separating them based on whitespace, and identifies special tokens like pipes (`|`), redirections (`<`, `<<`, `>`, `>>`), etc. Each token is stored in a linked list:

```c
typedef struct s_lexer
{
    char    	*str;
    t_tokens    token;
    int		    i;
    struct s_lexer	*next;
    struct s_lexer	*prev;
}	t_lexer;

