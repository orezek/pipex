/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_putnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:28:48 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/22 10:33:46 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_prt_putnbr(int n, int *ptr_chars_printed)
{
	char	*ptr;
	char	*or_ptr;

	ptr = ft_prt_itoa(n);
	or_ptr = ptr;
	while (*ptr)
		ft_prt_putchar(*(ptr++), ptr_chars_printed);
	free(or_ptr);
}
