/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:36:44 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/30 12:41:38 by orezek           ###   ########.fr       */
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
		return (ft_putstr_fd("Error: not enough arguments", 2), 1);
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
