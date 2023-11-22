/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:08:06 by orezek            #+#    #+#             */
/*   Updated: 2023/11/22 14:23:32 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "./gnl_utils/ft_gnl.h"

int	ft_initialize_buffer(int fd, char **buf)
{
	int	bytes_read;

	*buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buf)
		return (-1);
	bytes_read = read(fd, *buf, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(*buf);
		*buf = NULL;
		return (-1);
	}
	(*buf)[bytes_read] = '\0';
	return (0);
}

int	ft_has_newline(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc
		(sizeof(char) * (ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1));
	if (!new_str)
		return (NULL);
	if (s1)
	{
		while (s1[i])
			new_str[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
		new_str[j++] = s2[i++];
	new_str[j] = '\0';
	free(s1);
	return (new_str);
}

char	*ft_get_next_line(int fd)
{
	static char	*buf;
	char		*new_line;
	char		*temp;
	int			bytes_read;

	new_line = NULL;
	if (buf == NULL && ft_initialize_buffer(fd, &buf) == -1)
		return (NULL);
	if (!ft_has_newline(buf))
	{
		while (!ft_has_newline(buf))
		{
			new_line = ft_gnl_strjoin(new_line, buf);
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (bytes_read <= 0 && new_line[0] == '\0')
				return (free(buf), free(new_line), buf = NULL);
			if (bytes_read <= 0)
				return (free(buf), buf = NULL, new_line);
			buf[bytes_read] = '\0';
		}
		temp = ft_extract_line_and_movebytes(buf);
		return (new_line = ft_gnl_strjoin
			(new_line, temp), free(temp), new_line);
	}
	return (new_line = ft_extract_line_and_movebytes(buf));
}
