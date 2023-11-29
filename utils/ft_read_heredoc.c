/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:43:47 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 15:43:59 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_read_heredoc(char *limiter)
{
	char	*line;
	int		heredoc_fd;
	char	*clean_line;

	heredoc_fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	line = ft_get_next_line(STDIN_FILENO);
	clean_line = ft_sanitize_line(line);
	while (ft_pip_strncmp(clean_line, limiter, ft_strlen(limiter)) != 0)
	{
		write(heredoc_fd, line, ft_strlen(line) * sizeof(char));
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		free(line);
		free(clean_line);
		line = ft_get_next_line(STDIN_FILENO);
		clean_line = ft_sanitize_line(line);
	}
	close(heredoc_fd);
}
