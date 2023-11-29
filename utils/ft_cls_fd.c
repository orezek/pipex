/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cls_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:46:10 by orezek            #+#    #+#             */
/*   Updated: 2023/11/29 19:49:36 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_cls_fd(int *pipe_fd, int *io_fd, int no_of_commands)
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
