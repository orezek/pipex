/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:30:12 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:59:18 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *block, int c, size_t size)
{
	unsigned char	*ptr;
	unsigned char	byte;
	size_t			start;

	ptr = (unsigned char *) block;
	byte = (unsigned char) c;
	start = 0;
	while (start < size)
	{
		if (*(ptr + start) == byte)
			return ((void *)(ptr + start));
		start++;
	}
	return (NULL);
}
