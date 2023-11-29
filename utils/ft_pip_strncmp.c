/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pip_strncmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:10:03 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 15:10:19 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_pip_strncmp(const char *s1, const char *s2, size_t size)
{
	unsigned char		start;
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *) s1;
	str2 = (const unsigned char *) s2;
	start = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (start < size)
	{
		if (*(str1 + start) == '\0' && *(str2 + start) == '\0')
			break ;
		else if (*(str1 + start) < *(str2 + start))
			return (*(str1 + start) - *(str2 + start));
		else if (*(str1 + start) > *(str2 + start))
			return (*(str1 + start) - *(str2 + start));
		start++;
	}
	return (0);
}
