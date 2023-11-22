/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:30:25 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:59:11 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *to, const void *from, size_t size)
{
	size_t				step;
	unsigned char		*toptr;
	const unsigned char	*fromptr;

	toptr = (unsigned char *) to;
	fromptr = (unsigned char *) from;
	step = 0;
	if (to == NULL && from == NULL)
		return ((void *) toptr);
	while (step < size)
	{
		*(toptr + step) = *(fromptr + step);
		step++;
	}
	return ((void *) toptr);
}
