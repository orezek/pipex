/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:30:36 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:59:05 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *block, int c, size_t size)
{
	unsigned char	filler;
	unsigned char	*ptr;
	size_t			limit;

	filler = (unsigned char) c;
	ptr = (unsigned char *) block;
	limit = 0;
	while (limit < size)
	{
		*ptr = filler;
		limit++;
		ptr++;
	}
	return (ptr - size);
}
