/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cls_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:46:10 by orezek            #+#    #+#             */
/*   Updated: 2023/11/29 21:06:14 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_cls_fd(int *pipe_fd, int *io_fd, int no_of_commands)
{
	int	i;

	i = 0;
	while (i < 2 * no_of_commands)
	{
		if (pipe_fd[i] != -1)
		{
			if (close(pipe_fd[i]) == -1)
				perror("ft_cls_fd_while");
		}
		i++;
	}
	if (close(io_fd[0]) == -1 || close(io_fd[1]) == -1)
		perror("ft_cls_fd");
	free(io_fd);
}
