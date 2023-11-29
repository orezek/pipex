/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:21:20 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 15:27:05 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_get_command_path(char *envp[], char *cmd_arg)
{
	char	*cmd_path;
	char	**paths;
	char	**cmd_name;
	char	*tmp_path;
	char	**ptr_paths;

	cmd_name = ft_split(cmd_arg, ' ');
	paths = ft_get_paths(envp);
	ptr_paths = paths;
	while (*paths)
	{
		tmp_path = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(tmp_path, cmd_name[0]);
		free(tmp_path);
		if (ft_is_file_valid(cmd_path))
			return (free(ptr_paths), free(cmd_name), cmd_path);
		paths++;
	}
	return (free(ptr_paths), free(cmd_name), free(cmd_path), NULL);
}
