/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:29:48 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 15:30:04 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_exec_cmd(char *envp[], char *cmd_arg)
{
	char	**commands;
	char	*path;

	path = ft_get_command_path(envp, cmd_arg);
	commands = ft_split(cmd_arg, ' ');
	if (execve(path, commands, NULL) == -1)
		return (free(path), free(commands), -1);
	return (free(path), free(commands), 0);
}
