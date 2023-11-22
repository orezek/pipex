/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_putchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:49:52 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/22 10:33:29 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_prt_putchar(char c, int *ptr_chars_printed)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	write(1, &uc, sizeof(uc));
	*ptr_chars_printed += 1;
}
