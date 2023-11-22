/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:36:58 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:58:09 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *string, int c)
{
	int				len;
	unsigned char	letter;

	letter = (unsigned char) c;
	len = ft_strlen(string);
	if (letter == '\0')
		return ((char *) string + ft_strlen(string));
	len -= 1;
	while (len >= 0)
	{
		if (*(string + len) == letter)
			return ((char *) string + len);
		len--;
	}
	return (NULL);
}
