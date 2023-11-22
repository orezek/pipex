/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:24:23 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/22 14:03:54 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_gnl.h"

int	ft_gnl_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (*str++)
		i++;
	return (i);
}

int	ft_find_newline_position(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\n')
			return (i);
		i++;
		str++;
	}
	return (-1);
}

void	*ft_gnl_memmove(void *to, const void *from, size_t size)
{
	unsigned char		*des;
	const unsigned char	*src;

	des = to;
	src = from;
	if (des < src)
	{
		while (size--)
			*(des++) = *(src++);
	}
	else if (des > src)
	{
		des += size;
		src += size;
		while (size--)
			*--des = *--src;
	}
	return (to);
}

char	*ft_gnl_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_extract_line_and_movebytes(char *buf)
{
	char	*newline;
	int		nl_pos;

	nl_pos = ft_find_newline_position(buf);
	if (nl_pos >= 0)
	{
		newline = malloc(sizeof(char) * (nl_pos + 2));
		newline = ft_gnl_strncpy(newline, buf, nl_pos + 1);
		newline[nl_pos + 1] = '\0';
		buf = ft_gnl_memmove
			(buf, buf + nl_pos + 1, ft_gnl_strlen(buf) - nl_pos);
		return (newline);
	}
	return (NULL);
}
