/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:22:40 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/25 10:27:50 by aldokezer        ###   ########.fr       */
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
	int	no_of_commands;
	int	pipe_fd[2 * (argc - 3)];
	int pid;
	int process;

// argument check
	// if (argc != 6)
	// {
	// 	ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 cmdn file2", 2);
	// 	return (1);
	// }
	no_of_commands = argc - 3;
// create pipes for each command
	int i = 0;
	while (i < no_of_commands)
	{
		if (pipe(pipe_fd + (i++ * 2)) == -1)
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
	output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
		return (1);
	process = 0;
	while(process < no_of_commands)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			if (process == 0)
			{
				dup2(input_fd, STDIN_FILENO);
				dup2(pipe_fd[process * 2 + 1], STDOUT_FILENO);
			}
			if (process > 0 && process < no_of_commands - 1)
			{
				dup2(pipe_fd[process * 2 - 2], STDIN_FILENO);
				dup2(pipe_fd[process * 2 + 1], STDOUT_FILENO);
			}
			if (process == no_of_commands - 1)
			{
				dup2(pipe_fd[process * 2 - 2], STDIN_FILENO);
				dup2(output_fd, STDOUT_FILENO);
			}
			int i = 0;
			while (i < 2 * no_of_commands)
				close(pipe_fd[i++]);// close all pipes
			close(output_fd);
			close(input_fd);
			char *wc_argss[] = { "cat", NULL };
			execve("/bin/cat", wc_argss, NULL);
		}
		else
		{
			close(pipe_fd[process * 2 + 1]); // write end of the pipe
			wait(NULL);
		}
		ft_putnbr_fd(process, 1);
		process++;
	}
}
