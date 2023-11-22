/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:29:00 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 18:00:11 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t eltsize)
{
	void	*ptr;

	ptr = malloc(count * eltsize);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, count * eltsize);
	return (ptr);
}
