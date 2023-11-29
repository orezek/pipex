/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:28:29 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 14:33:59 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	*ft_create_pipes(int no_of_commands)
{
	int	*pipe_fd;
	int	i;

	pipe_fd = malloc((2 * no_of_commands) * sizeof(int));
	if (!pipe_fd)
		return (perror("malloc for pipes array"), NULL);
	i = 0;
	while (i < no_of_commands)
	{
		if (pipe(pipe_fd +(i++ *2)) == -1)
			return (perror("create pipes"), NULL);
	}
	return (pipe_fd);
}
