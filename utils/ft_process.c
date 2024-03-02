/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:43:23 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/02 13:46:14 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_process(int *process, int no_of_commands)
{
	static int	s_process;

	*process = s_process;
	if (s_process < no_of_commands)
		return (s_process++, 1);
	else
		return (0);
}
