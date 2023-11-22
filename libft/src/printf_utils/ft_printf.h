/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:41:29 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/22 14:22:00 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>

int		ft_printf(const char *format, ...);
void	ft_prt_putchar(char c, int *ptr_chars_printed);
void	ft_prt_putstr(char *str, int *ptr_chars_printed);
void	ft_prt_putnbr(int n, int *ptr_chars_printed);
char	*ft_prt_itoa(int n);
char	*ft_prt_unsigned_itoa(int n);
void	ft_prt_putnbr_unsigned(unsigned int n, int *ptr_chars_printed);
char	*ft_prt_convert_number_to_hex(uint64_t bin_n);
int		ft_prt_strlen(char *str);
int		ft_prt_hexlen(uint64_t bin_n);
char	*ft_prt_convert_pointer_to_hex(uint64_t bin_n);
char	*ft_prt_strcpy(char *dest, char *src);
void	ft_prt_putptr(void *ptr_address, int *ptr_chars_printed);
void	ft_prt_puthex(unsigned int ptr_address, int *ptr_chars_printed);
int		ft_prt_toupper(int c);
void	ft_prt_puthex_upper(unsigned int ptr_address, int *ptr_chars_printed);
void	ft_prt_putstr_upper(char *str, int *ptr_chars_printed);
char	*ft_prt_strdup(char *src);
int		ft_prt_printf_short(char *format,
			int *ptr_chars_printed, va_list *args);
#endif
