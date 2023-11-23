/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:22:40 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/23 12:16:04 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_file_valid(const char *filename)
{
	if (access(filename, F_OK | R_OK) == 0)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	int	input_fd;
	int	output_fd;
	int	pipe_fd[2];
	int pid;
// argument check
	if (argc != 4)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 ile2", 2);
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
	output_fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);

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
		// connect data streams
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
		// execute command
		char *wc_args[] = { "wc -l", NULL };
		execve("/usr/bin/wc", wc_args, NULL);
	}
// parent process execution
	else
	{
		close(pipe_fd[0]);
        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0)
		{
            write(pipe_fd[1], buffer, bytes_read);
        }
        close(input_fd);
        close(pipe_fd[1]);
// wait for child process to finish
        waitpid(pid, NULL, 0);
	}
	return (0);
}
