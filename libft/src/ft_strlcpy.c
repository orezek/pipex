/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:30:58 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:58:26 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *to, const char *from, size_t size)
{
	size_t		src_size;
	size_t		sizet;
	const char	*end;

	src_size = ft_strlen(from);
	sizet = size;
	end = from + (sizet - 1);
	if (sizet > src_size)
	{
		while (*from)
			*(to++) = *(from++);
		*to = '\0';
	}
	else if (sizet > 0 && sizet <= src_size)
	{
		while (from < end)
			*(to++) = *(from++);
		*to = '\0';
	}
	return (src_size);
}
