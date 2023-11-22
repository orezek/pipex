/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:31:12 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:58:44 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *string, int c)
{
	unsigned char	letter;

	letter = c;
	if (letter == '\0')
		return ((char *) string + ft_strlen(string));
	while (*string)
	{
		if (*string == letter)
			return ((char *) string);
		string++;
	}
	return (NULL);
}
