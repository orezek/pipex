/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:23:54 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 19:12:46 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include "./libft/libft.h"

int		ft_is_file_valid(const char *filename);
int		ft_pip_strncmp(const char *s1, const char *s2, size_t size);
char	**ft_get_paths(char *envp[]);
char	*ft_get_command_path(char *envp[], char *cmd_arg);
int		ft_exec_cmd(char *envp[], char *cmd_arg);
char	*ft_sanitize_line(char *str);
void	ft_read_heredoc(char *limiter);
int		ft_create_io_fd(char *argv[], int argc, int *input_fd, int *output_fd);
void	ft_cls_fd(int *pipe_fd, int input_fd, int output_fd, int no_of_cmds);
int		*ft_create_pipes(int no_of_cmds);
void	ft_redir_pipes(int input_fd, int output_fd, int process, int *pipe_fd, int no_of_cmds);
int		ft_is_heredoc(char *argv[]);
int		ft_no_cmd(int argc, char *argv[]);
int		ft_process(int *process, int no_of_cmds);
int		ft_check_args(int argc, char **argv, char **envp);
#endif
