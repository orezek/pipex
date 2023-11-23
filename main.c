/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:22:40 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/23 19:02:57 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// the commands are harcoded for now and the program will output from the file1 to file2
// through 1 cat command and 2 wc command
#include "pipex.h"

int	ft_is_file_valid(const char *filename)
{
	if (access(filename, F_OK | R_OK) == 0)
		return (1);
	return (0);
}

void ft_print_from_fd(int fd)
{
	char buffer[1024];
	ssize_t bytes_read;

	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		ft_putstr_fd(buffer, 1);
	}
}

// child process is a duplicate of the parent process until execve() is called
// forked process iherits all from the main process the same applies to child processes and its children
// forked process has its own copy of the variables and file descriptors, the file descriptors
// are not shared between the parent and the child process and need to be manually closed when not needed!!!
// the child process can write to the pipe and the parent process can read from the pipe and vice versa

int	main(int argc, char *argv[])
{
	int	input_fd;
	int	output_fd;
	int	pipe_fd[2];
	int pid;
// argument check
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		return (1);
	}
// file check of the first argument
	if (!ft_is_file_valid(argv[1]))
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
// create input and output file descriptors
	input_fd = open(argv[1], O_RDONLY);
	output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
		return (1);
// create pipe in parent process
	if (pipe(pipe_fd) == -1)
		return (1);
// create child process
	pid = fork();
// check if fork failed
	if (pid == -1)
		return (1);
// child process execution
	if (pid == 0)
	{
		int pid2;
		int pipe_fd2[2];

		if (pipe(pipe_fd2) == -1)
			return (1);
		// create subchild process
		pid2 = fork();
		if (pid2 == -1)
			return (1);
		// subchild process execution a child of the child process executes in parallel with the child process
		if (pid2 == 0)
		{
			// this was crazy! 3 hours of debugging and it was just a close() missing
			// lesson learned: close all file descriptors that are not needed
			// the child process inherits all file descriptors from the parent processes
			// so you must close ALL ALL ALL!!
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			close(pipe_fd2[1]);
			dup2(pipe_fd2[0], STDIN_FILENO);
			//ft_print_from_fd(pipe_fd2[0]);
			close(pipe_fd2[0]);
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
			char *wc_args[] = { "wc", NULL };
			execve("/usr/bin/wc", wc_args, NULL);
		}
		// child process execution
		// child of the main process
		else
		{
			// close pipe_fd[1] - not needed for writing in the child process to the main process
			close(pipe_fd[1]);
			close(pipe_fd2[0]);
			// connect the pipe from the main process to the stdin of the child process (ls)
			//ft_print_from_fd(pipe_fd[0]);
			dup2(pipe_fd[0], STDIN_FILENO);
			//- no longer needed
			close(pipe_fd[0]);
			// connect the pipe from the child process to the write end of the pipe of the subchild process
			dup2(pipe_fd2[1], STDOUT_FILENO);
			//ft_putnbr_fd(dup2(output_fd, STDOUT_FILENO), 1);
			//close(output_fd);
			close(pipe_fd2[1]);
			// execute command
			char *wc_argss[] = { "cat", NULL };
			execve("/bin/cat", wc_argss, NULL);
			waitpid(pid2, NULL, 0);
		}
	}
// parent process execution - executes in parallel with child process!
// (pid == 0) is the child process
	else
	{
		// close pipe_fd[0] - not needed for reading in the parent process
		close(pipe_fd[0]);
		// initialize buffer
        char buffer[1];
		// initialize bytes_read
        ssize_t bytes_read;
		// read input_fd and write to pipe_fd[1]
        while ((bytes_read = read(input_fd, buffer, 1)) > 0)
		{
            write(pipe_fd[1], buffer, bytes_read);
        }
		// close input_fd and pipe_fd[1] - no longer needed
        close(input_fd);
        close(pipe_fd[1]);
// wait for child process to finish
        waitpid(pid, NULL, 0);
	}
	return (0);
}
