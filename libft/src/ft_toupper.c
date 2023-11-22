/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:37:08 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:57:47 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	ft_islower(int c)
{
	unsigned char	letter;

	if (c == EOF)
		return (0);
	letter = (unsigned char) c;
	if (letter >= 'a' && letter <= 'z')
		return (1);
	return (0);
}

int	ft_toupper(int c)
{
	if (ft_isalpha(c) && ft_islower(c))
		return (c - 32);
	return (c);
}
