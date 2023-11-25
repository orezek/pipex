/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:22:40 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/26 00:28:13 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// the commands are harcoded for now and the program will output from the file1 to file2
// through 1 cat command and 2 wc command
#include "pipex.h"

int	ft_is_file_valid(const char *filename)
{
	if (access(filename, R_OK) == 0)
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

char	**ft_get_paths(char *envp[])
{
	int		i = 0;
	char	*path;

	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i] + 5;
		i++;
	}
	return (ft_split(path, ':'));
}
// return path to command if the command exists
char	*ft_get_command_path(char *envp[], char *cmd_arg)
{
	char	*cmd_path;
	char	**paths;
	char	**cmd_name;
	char	*tmp_path;
	char	**ptr_paths;

	cmd_name = ft_split(cmd_arg, ' ');
	paths = ft_get_paths(envp);
	ptr_paths = paths;
	while (*paths)
	{
		tmp_path = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(tmp_path, cmd_name[0]);
		free(tmp_path);
		if (ft_is_file_valid(cmd_path))
				return (free(ptr_paths), free(cmd_name), cmd_path);
		paths++;
	}
	return (free(ptr_paths), free(cmd_name), free(cmd_path), NULL);
}

// Execute process
int	ft_exec_cmd(char *path, char *cmd_arg)
{
	char	**commands;

	commands = ft_split(cmd_arg, ' ');
	if (execve(path, commands, NULL) == -1)
		return (free(commands), -1);
	return (free(commands), 0);
}

int	main(int argc, char *argv[], char *envp[])
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
			char *path = ft_get_command_path(envp, argv[process + 2]);
			// ft_exec_cmd(path, argv[process + 2]);
			// free(path);
			char **wc_argss = ft_split(argv[process + 2], ' ');
			execve(path, wc_argss, NULL);
			free(wc_argss);
		}
		else
		{
			close(pipe_fd[process * 2 + 1]); // write end of the pipe
			wait(NULL);
		}
		//ft_putnbr_fd(process, 1);
		process++;
	}
}
