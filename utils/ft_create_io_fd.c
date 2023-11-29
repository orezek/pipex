/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_io_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:48:08 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 19:59:47 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_create_io_fd(char *argv[], int argc, int **io_fd)
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
