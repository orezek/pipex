/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_printf_short.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:12:45 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/22 10:33:25 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_prt_printf_short(char *format, int *ptr_chars_printed, va_list *args)
{
	if (*format == 's')
		ft_prt_putstr(va_arg(*args, char *), ptr_chars_printed);
	else if (*format == 'd')
		ft_prt_putnbr(va_arg(*args, int), ptr_chars_printed);
	else if (*format == 'c')
		ft_prt_putchar(va_arg(*args, int), ptr_chars_printed);
	else if (*format == 'p')
		ft_prt_putptr(va_arg(*args, void *), ptr_chars_printed);
	else if (*format == 'i')
		ft_prt_putnbr(va_arg(*args, int ), ptr_chars_printed);
	else if (*format == 'u')
		ft_prt_putnbr_unsigned(va_arg(*args, unsigned int), ptr_chars_printed);
	else if (*format == 'x')
		ft_prt_puthex(va_arg(*args, unsigned int), ptr_chars_printed);
	else if (*format == 'X')
		ft_prt_puthex_upper(va_arg(*args, unsigned int), ptr_chars_printed);
	else if (*format == '%')
		ft_prt_putchar('%', ptr_chars_printed);
	else
		return (-1);
	return (0);
}
