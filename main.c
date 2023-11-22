/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:22:40 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/22 19:03:44 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_file_valid(const char *filename)
{
	if (access(filename, F_OK | R_OK) == 0)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		return (1);
	}
	if (!ft_is_file_valid(argv[1]))
	{
		ft_putstr_fd("Error: file1 is invalid", 2);
		return (1);
	}
	if (ft_is_file_valid(argv[1]))
	{
		int	fd;
		char *line;
		fd = open(argv[1], O_RDONLY);
		line = ft_get_next_line(fd);
		while (line)
		{
			ft_printf("%s", line);
			free(line);
			line = ft_get_next_line(fd);
		}
	}

	return (0);
}
