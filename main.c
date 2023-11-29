/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:22:40 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 19:13:34 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_create_int_array(int **array)
{
	*array = malloc(2 * sizeof(int));
	(*array)[0] = 88;
	*(*array + 1) = 100;
}

int	tst_ft_create_io_fd(char *argv[], int argc, int **io_fd)
{
	*io_fd = malloc(2 *  sizeof(int));
	if (ft_pip_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		ft_read_heredoc(argv[2]);
		(*io_fd)[0] = open(argv[1], O_RDONLY);
		(*io_fd)[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((*io_fd)[1] == -1 || (*io_fd)[0] == -1)
			return (perror("heredoc file open"), -1);
	}
	else
	{
		(*io_fd)[0] = open(argv[1], O_RDONLY);
		(*io_fd)[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((*io_fd)[1] == -1 || (*io_fd)[0] == -1)
			return (perror("input file open"), -1);
	}
	return (0);
}

void	tst_ft_redir_pipes(int *io_fd, int process, int *pipe_fd, int no_of_commands)
{
	ft_putnbr_fd(io_fd[0], 1);
	ft_putnbr_fd(io_fd[1], 1);
	if (process == 0)
	{
		dup2(io_fd[0], STDIN_FILENO);
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
		dup2(io_fd[1], STDOUT_FILENO);
	}
}

void	tst_ft_cls_fd(int *pipe_fd, int *io_fd, int no_of_commands)
{
	int	i;

	i = 0;
	while (i < 2 * no_of_commands)
	{
		if (close(pipe_fd[i++]) == -1)
			perror("ft_cls_fd_while");
	}
	if (close(io_fd[0]) == -1 || close(io_fd[1]) == -1)
		perror("ft_cls_fd");
	free(io_fd);
}
int	main(int argc, char *argv[], char *envp[])
{
	int	*io_fd;
	int	pid;
	int	process;
	int	*pipe_fd;

	if (ft_check_args(argc, argv, envp))
		return (1);
	pipe_fd = ft_create_pipes(ft_no_cmd(argc, argv));
	tst_ft_create_io_fd(argv, argc, &io_fd);
	while (ft_process(&process, ft_no_cmd(argc, argv)))
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			tst_ft_redir_pipes(io_fd, process, pipe_fd, ft_no_cmd(argc, argv));
			tst_ft_cls_fd(pipe_fd, io_fd, ft_no_cmd(argc, argv));
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
