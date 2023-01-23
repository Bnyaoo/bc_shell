# bc_shell

- takes user input as command line arguments
- parses user input to find the PATH of a command
- forks the parent process
- calls UNIX system call to execute the parsed command, (using execv)
- supports basic I/O redirection (stdin, stdout, stderr)
- builtin function to support 'cd' commands, (cd, cd ~, cd .., cd ../.., etc.)
- compilation with 'gcc' command and './a.out' to run executable
- newline feature to accept enter as a valid user input without terminating
- 'exit' command to exit child process and return to real shell
