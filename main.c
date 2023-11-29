/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:22:40 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 14:51:32 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_file_valid(const char *filename)
{
	if (access(filename, R_OK) == 0)
		return (1);
	return (0);
}

int	ft_pip_strncmp(const char *s1, const char *s2, size_t size)
{
	unsigned char		start;
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *) s1;
	str2 = (const unsigned char *) s2;
	start = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (start < size)
	{
		if (*(str1 + start) == '\0' && *(str2 + start) == '\0')
			break ;
		else if (*(str1 + start) < *(str2 + start))
			return (*(str1 + start) - *(str2 + start));
		else if (*(str1 + start) > *(str2 + start))
			return (*(str1 + start) - *(str2 + start));
		start++;
	}
	return (0);
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
// Sanitize line = remove the \n char
char *ft_sanitize_line(char *str)
{
	int	len;
	char *new_line;
	int	i;

	if (str == NULL)
		return NULL;
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
	{
		new_line = malloc (len * sizeof(char));
		if (!new_line)
			return (NULL);
		i = 0;
		while (i < len - 1)
		{
			new_line[i] = str[i];
			i++;
		}
		new_line[i] = '\0';
		return (new_line);
	}
	return (str);
}

// read heredoc and save the text to a temp file
void	ft_read_heredoc(char *limiter)
{
	char	*line;
	int		heredoc_fd;
	char	*clean_line;

	heredoc_fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	line = ft_get_next_line(STDIN_FILENO);
	clean_line = ft_sanitize_line(line);
	while (ft_pip_strncmp(clean_line, limiter, ft_strlen(limiter)) != 0)
	{
		write(heredoc_fd, line, ft_strlen(line) * sizeof(char));
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		free(line);
		free(clean_line);
		line = ft_get_next_line(STDIN_FILENO);
		clean_line = ft_sanitize_line(line);
	}
	close(heredoc_fd);
}

int	ft_create_io_fd(char *argv[], int argc, int *input_fd, int *output_fd)
{
	if (ft_pip_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		ft_read_heredoc(argv[2]);
		*input_fd = open(argv[1], O_RDONLY);
		*output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND , 0644);
		if (*output_fd == -1 || *input_fd == -1)
			return (perror("heredoc file open"), -1);
	}
	else
	{
		*input_fd = open(argv[1], O_RDONLY);
		*output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*output_fd == -1 || *input_fd == -1)
			return (perror("input file open"), -1);
	}
	return (0);
}

//Done
// void	ft_cls_fd(int *pipe_fd, int input_fd, int output_fd, int no_of_commands)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 2 * no_of_commands)
// 	{
// 		if (close(pipe_fd[i++]) == -1)
// 		{
// 			//perror("while");
// 			//ft_putnbr_fd(pipe_fd[i - 1], 2); // prints FD that are already closed
// 			//ft_putchar_fd('\n', 2);
// 		}
// 	}
// 	if (close(output_fd) == -1 || close(input_fd) == -1)
// 		perror("ft_cls_fd");
// }

//Done
// int	*ft_create_pipes(int no_of_commands)
// {
// 	int *pipe_fd;
// 	int i;

// 	pipe_fd = malloc((2 * no_of_commands) * sizeof(int));
// 	if (!pipe_fd)
// 		return (perror("malloc for pipes array"), NULL);
// 	i = 0;
// 	while (i < no_of_commands)
// 	{
// 		if (pipe(pipe_fd + (i++ * 2)) == -1)
// 			return (perror("create pipes"), NULL);
// 	}
// 	return (pipe_fd);
// }

void	ft_redir_pipes(int input_fd, int output_fd, int process, int *pipe_fd, int no_of_commands)
{
	if (process == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(pipe_fd[process * 2 + 1], STDOUT_FILENO);
	}
	else if (process > 0 && process < no_of_commands - 1)
	{
		dup2(pipe_fd[process * 2 - 2], STDIN_FILENO);
		dup2(pipe_fd[process * 2 + 1], STDOUT_FILENO);
	}
	else if (process == no_of_commands - 1)
	{
		dup2(pipe_fd[process * 2 - 2], STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
	}
}

// Done
// int	ft_is_heredoc(char *argv[])
// {
// 	if (ft_pip_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
// 		return (1);
// 	else
// 		return (0);
// }

int	ft_no_of_commands(int argc, char *argv[])
{
	return (argc - (3 + ft_is_heredoc(argv)));
}

// Done
// process interator - instead of variable I am using static variable to keep process iterations
// int	ft_process(int *process, int no_of_commands)
// {
// 	int	static s_process;

// 	*process = s_process;
// 	if (s_process < no_of_commands)
// 		return (s_process++, 1);
// 	else
// 		return (0);
// }

//Done
// int	ft_check_args(int argc, char **argv, char **envp)
// {
// 	int i;

// 	i = 2;
// 	if ((ft_is_heredoc(argv) && argc < 6) || (ft_is_file_valid(argv[1]) && argc < 5))
// 		return (perror("not enough arguments"), 1);
// 	if (!ft_is_heredoc(argv) && !ft_is_file_valid(argv[1]))
// 			return (perror(argv[1]), 1);

// 	if (ft_is_heredoc(argv))
// 		i = 3;
// 	while (i < argc - 1)
// 	{
// 		if (ft_get_command_path(envp, argv[i]) == NULL)
// 			return (perror(argv[i]), 1);
// 		i++;
// 	}
// 	return (0);
// }

int	main(int argc, char *argv[], char *envp[])
{
	int	input_fd;
	int	output_fd;
	int	pid;
	int	process;
	int	*pipe_fd;

	if (ft_check_args(argc, argv, envp))
		return (1);
	pipe_fd = ft_create_pipes(ft_no_of_commands(argc, argv));
	ft_create_io_fd(argv, argc, &input_fd, &output_fd);
	while (ft_process(&process, ft_no_of_commands(argc, argv)))
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			ft_redir_pipes(input_fd, output_fd, process, pipe_fd, ft_no_of_commands(argc, argv));
			ft_cls_fd(pipe_fd, input_fd, output_fd, ft_no_of_commands(argc, argv));
			ft_exec_cmd(envp, argv[process + (2 + ft_is_heredoc(argv))]);
		}
		else
		{
			close(pipe_fd[process * 2 + 1]);
			wait(NULL);
		}
	}
	return (free(pipe_fd), unlink("here_doc"), 0);
}
