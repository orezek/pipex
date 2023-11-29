/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:51:05 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 19:55:54 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_redir_pipes(int *io_fd, int process, int *pipe_fd, int no_of_cmds)
{
	if (process == 0)
	{
		dup2(io_fd[0], STDIN_FILENO);
		dup2(pipe_fd[process * 2 + 1], STDOUT_FILENO);
	}
	else if (process > 0 && process < no_of_cmds - 1)
	{
		dup2(pipe_fd[process * 2 - 2], STDIN_FILENO);
		dup2(pipe_fd[process * 2 + 1], STDOUT_FILENO);
	}
	else if (process == no_of_cmds - 1)
	{
		dup2(pipe_fd[process * 2 - 2], STDIN_FILENO);
		dup2(io_fd[1], STDOUT_FILENO);
	}
}
