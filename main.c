/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:22:40 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/30 00:50:57 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	*io_fd;
	int	pid;
	int	ps;
	int	*pipe_fd;

	if (ft_check_args(argc, argv, envp))
		return (1);
	pipe_fd = ft_create_pipes(ft_no_cmd(argc, argv));
	if (ft_create_io_fd(argv, argc, &io_fd))
		return (1);
	while (ft_process(&ps, ft_no_cmd(argc, argv)))
	{
		pid = fork();
		if (pid == 0)
		{
			ft_redir_pipes(io_fd, ps, pipe_fd, ft_no_cmd(argc, argv));
			ft_cls_fd(pipe_fd, io_fd, ft_no_cmd(argc, argv));
			return (ft_exec_cmd(envp, argv[ps + (2 + ft_is_heredoc(argv))]), 0);
		}
		close(pipe_fd[ps * 2 + 1]);
		pipe_fd[ps * 2 + 1] = -1;
		wait(NULL);
	}
	return (free(pipe_fd), free(io_fd), unlink("here_doc"), 0);
}
