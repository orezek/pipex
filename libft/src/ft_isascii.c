/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:29:42 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 18:00:02 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isascii(int c)
{
	unsigned char	letter;

	if (c == EOF)
		return (0);
	if (c < 256)
	{
		letter = (unsigned char) c;
		if (letter <= 127)
			return (1);
	}
	return (0);
}
