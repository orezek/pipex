/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:30:47 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:58:30 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *to, const char *from, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	step;

	src_len = ft_strlen(from);
	dst_len = ft_strlen(to);
	step = dst_len;
	to += dst_len;
	if (size <= dst_len)
		return (src_len + size);
	else if (src_len + dst_len >= size)
	{
		while (step++ < size - 1)
			*(to++) = *(from++);
		*to = '\0';
	}
	else
	{
		while (step++ < size && *from)
			*(to++) = *(from++);
		*to = '\0';
	}
	return (src_len + dst_len);
}
