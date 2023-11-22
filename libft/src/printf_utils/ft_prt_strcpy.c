/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_strcpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:15:06 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/22 10:34:05 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_prt_strcpy(char *des, char *src)
{
	char	*ptr_des;

	ptr_des = des;
	while (*src)
	{
		*des++ = *src++;
	}
	*des = '\0';
	return (ptr_des);
}
