/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:38:29 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 15:39:40 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_sanitize_line(char *str)
{
	int		len;
	char	*new_line;
	int		i;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
	{
		new_line = malloc (len * sizeof(char));
		if (!new_line)
			return (NULL);
		i = 0;
		while (i < len - 1)
		{
			new_line[i] = str[i];
			i++;
		}
		new_line[i] = '\0';
		return (new_line);
	}
	return (str);
}
