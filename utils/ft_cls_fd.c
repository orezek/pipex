/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cls_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:46:10 by orezek            #+#    #+#             */
/*   Updated: 2023/11/29 11:49:11 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_cls_fd(int *pipe_fd, int input_fd, int output_fd, int no_of_commands)
{
	int	i;

	i = 0;
	while (i < 2 * no_of_commands)
	{
		if (close(pipe_fd[i++]) == -1)
			perror("ft_cls_fd_while");
	}
	if (close(output_fd) == -1 || close(input_fd) == -1)
		perror("ft_cls_fd");
}
