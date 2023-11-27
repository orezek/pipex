/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:22:40 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/27 21:16:14 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// get PATH string from env variables
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
int	ft_exec_cmd(char *envp[], char *cmd_arg)
{
	char	**commands;
	char	*path;

	path = ft_get_command_path(envp, cmd_arg);
	commands = ft_split(cmd_arg, ' ');
	if (execve(path, commands, NULL) == -1)
		return (free(path), free(commands), -1);
	return (free(path), free(commands), 0);
}

// read heredoc and save the text to a temp file
void	ft_read_heredoc(char *limiter)
{
	char	*line;
	int		heredoc_fd;

	heredoc_fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	line = ft_get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, limiter, ft_strlen(limiter) * sizeof(char)) != 0)
	{
		write(heredoc_fd, line, ft_strlen(line) * sizeof(char));
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		free(line);
		line = ft_get_next_line(STDIN_FILENO);
	}
	close(heredoc_fd);
}
// create input and output files
int	ft_create_io_fd(char *argv[], int argc, int *is_heredoc, int *input_fd, int *output_fd)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		*is_heredoc = 1;
		ft_read_heredoc(argv[2]);
		*input_fd = open(argv[1], O_RDONLY);
		*output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND , 0644);
		if (*output_fd == -1 || *input_fd == -1)
			return (perror("heredoc file open"), -1);
	}
	else
	{
		*is_heredoc = 0;
		*input_fd = open(argv[1], O_RDONLY);
		*output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*output_fd == -1 || *input_fd == -1)
			return (perror("input file open"), -1);
	}
	return (0);
}

void	ft_close_fd(int *pipe_fd, int input_fd, int output_fd, int no_of_commands)
{
	int	i;

	i = 0;
	while (i < 2 * no_of_commands)
	{
		if (close(pipe_fd[i++]) == -1)
		{
			//perror("while");
			//ft_putnbr_fd(pipe_fd[i - 1], 2); // prints FD that are already closed
			//ft_putchar_fd('\n', 2);
		}
	}
	if (close(output_fd) == -1 || close(input_fd) == -1)
		perror("fd");
}
int	*ft_create_pipes(int no_of_commands)
{
	int *pipe_fd;
	int i;

	pipe_fd = malloc((2 * no_of_commands) * sizeof(int));
	if (!pipe_fd)
		return (perror("malloc for pipes array"), NULL);
	i = 0;
	while (i < no_of_commands)
	{
		if (pipe(pipe_fd + (i++ * 2)) == -1)
			return (perror("create pipes"), NULL);
	}
	return (pipe_fd);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	input_fd;
	int	output_fd;
	int	no_of_commands;
	int	is_heredoc;
	int	pid;
	int	process;
	int	*pipe_fd;
// argument check
	// if (argc != 6)
	// {
	// 	ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 cmdn file2", 2);
	// 	return (1);
	// }

// // file check of the first argument
// 	if (!ft_is_file_valid(argv[1]))
// 	{
// 		ft_putstr_fd("pipex: no such file or directory: ", 2);
// 		ft_putstr_fd(argv[1], 2);
// 		ft_putstr_fd("\n", 2);
// 		return (1);
// 	}
	if (ft_create_io_fd(argv, argc, &is_heredoc, &input_fd, &output_fd) == -1)
		return (1);
	no_of_commands = argc - (3 + is_heredoc);
// create pipes for each command
	pipe_fd = ft_create_pipes(no_of_commands);
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
			ft_close_fd(pipe_fd, input_fd, output_fd, no_of_commands);
			ft_exec_cmd(envp, argv[process + (2 + is_heredoc)]);
		}
		else
		{
			close(pipe_fd[process * 2 + 1]);
			wait(NULL);
		}
		process++;
	}
	return (free(pipe_fd), unlink("here_doc"), 0);
}
