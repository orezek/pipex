/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_io_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:48:08 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 15:49:08 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_create_io_fd(char *argv[], int argc, int *input_fd, int *output_fd)
{
	if (ft_pip_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		ft_read_heredoc(argv[2]);
		*input_fd = open(argv[1], O_RDONLY);
		*output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
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
