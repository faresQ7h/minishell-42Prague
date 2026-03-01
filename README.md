*This project has been created as part of the 42 curriculum by fares-_-q7h, farmoham.*

# Minishell

## Description
`minishell` is a small Unix shell written in C.

The goal of the project is to understand how shells work by implementing core behavior manually:
- interactive prompt with command reading
- lexical analysis and parsing of user input
- environment variable expansion
- execution of builtins and external commands
- pipes and redirections (`<`, `>`, `>>`, `<<`)
- signal handling for interactive mode and heredoc

This project uses `readline` for input/history and `libft` as a utility library.

## Features
- Builtins: `echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit`
- External command execution using `PATH`
- Pipelines (`|`) and command chaining through process creation
- Redirections including heredoc with delimiter support
- Quote handling and basic syntax validation
- Environment list management and `$VAR` expansion

## Instructions
### Requirements
- Linux (or a Unix-like environment)
- `cc` compiler
- `make`
- `readline` and `history` libraries (link flags: `-lreadline -lhistory`)

### Build
```bash
make
```

### Run
```bash
./minishell
```

### Common Make Targets
```bash
make        # build minishell
make clean  # remove object files
make fclean # remove objects and binary
make re     # full rebuild
```

### Quick Usage Examples
```bash
minishell$ echo hello
minishell$ export USERNAME=student
minishell$ echo $USERNAME
minishell$ ls -l | grep minishell
minishell$ cat << EOF
> line 1
> line 2
> EOF
```

## Resources
Classic references used for this project:
- GNU Bash Manual: https://www.gnu.org/software/bash/manual/
- POSIX Shell Command Language: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
- GNU Readline Manual: https://tiswww.case.edu/php/chet/readline/readline.html
- Linux man pages: `man 2 fork`, `man 2 execve`, `man 2 waitpid`, `man 7 signal`, `man 3 readline`

### AI usage
AI tools were used as an assistant for:
- discussing debugging strategies
- validating edge cases (especially signal/heredoc behavior)
- improving documentation quality and structure (this README)

All final code integration, testing, and project decisions were reviewed and validated in the local project environment.
