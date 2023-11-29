/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:36:44 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/30 00:20:27 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_check_args(int argc, char **argv, char **envp)
{
	int	i;

	i = 2;
	if (argc == 1)
		return (perror(argv[0]), 1);
	if ((ft_is_heredoc(argv) && argc < 6)
		|| (ft_is_file_valid(argv[1]) && argc < 5))
		return (perror("not enough arguments"), 1);
	if (!ft_is_heredoc(argv) && !ft_is_file_valid(argv[1]))
		return (perror(argv[1]), 1);
	if (ft_is_heredoc(argv))
		i = 3;
	while (i < argc - 1)
	{
		if (ft_get_command_path(envp, argv[i]) == NULL)
			return (perror(argv[i]), 1);
		i++;
	}
	return (0);
}
