/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:30:19 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:59:15 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *a1, const void *a2, size_t size)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			step;

	ptr1 = (unsigned char *) a1;
	ptr2 = (unsigned char *) a2;
	step = 0;
	while (step < size)
	{
		if (*(ptr1 + step) < *(ptr2 + step))
			return (*(ptr1 + step) - *(ptr2 + step));
		else if ((*(ptr1 + step) > *(ptr2 + step)))
			return (*(ptr1 + step) - *(ptr2 + step));
		step++;
	}
	return (0);
}
