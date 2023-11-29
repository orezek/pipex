/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:22:40 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 20:28:18 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	*io_fd;
	int	pid;
	int	process;
	int	*pipe_fd;

	if (ft_check_args(argc, argv, envp))
		return (1);
	pipe_fd = ft_create_pipes(ft_no_cmd(argc, argv));
	ft_create_io_fd(argv, argc, &io_fd);
	while (ft_process(&process, ft_no_cmd(argc, argv)))
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			ft_redir_pipes(io_fd, process, pipe_fd, ft_no_cmd(argc, argv));
			ft_cls_fd(pipe_fd, io_fd, ft_no_cmd(argc, argv));
			ft_exec_cmd(envp, argv[process + (2 + ft_is_heredoc(argv))]);
			return (0);
		}
		close(pipe_fd[process * 2 + 1]);
		wait(NULL);
	}
	return (free(pipe_fd), free(io_fd), unlink("here_doc"), 0);
}
