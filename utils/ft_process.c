/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:43:23 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 14:44:06 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_process(int *process, int no_of_commands)
{
	int static	s_process;

	*process = s_process;
	if (s_process < no_of_commands)
		return (s_process++, 1);
	else
		return (0);
}
