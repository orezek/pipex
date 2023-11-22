/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:30:30 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:59:08 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *to, const void *from, size_t size)
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
