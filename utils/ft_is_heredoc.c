/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:46:29 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 14:54:11 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_is_heredoc(char *argv[])
{
	if (ft_pip_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		return (1);
	else
		return (0);
}
