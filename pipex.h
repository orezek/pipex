/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:23:54 by aldokezer         #+#    #+#             */
/*   Updated: 2023/11/29 21:09:16 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include "./libft/libft.h"

// check if a file is valid by using access()
int		ft_is_file_valid(const char *filename);
// compare strings but check if the strings have the same length first
int		ft_pip_strncmp(const char *s1, const char *s2, size_t size);
// get PATH string from envp system array
char	**ft_get_paths(char *envp[]);
// get command paths for a given command from the env var PATH
char	*ft_get_command_path(char *envp[], char *cmd_arg);
// execute commands in the child processes - execve()
int		ft_exec_cmd(char *envp[], char *cmd_arg);
// remove the \n from the line returned when here_doc is selected from STDIN
char	*ft_sanitize_line(char *str);
// read here_doc ie STDIN until limiter sentinel is found
void	ft_read_heredoc(char *limiter);
// create an array of input and output FD for file manipulation
int		ft_create_io_fd(char *argv[], int argc, int **io_fd);
// close file descriptors after child process execution
void	ft_cls_fd(int *pipe_fd, int *io_fd, int no_of_commands);
// create an array of pipes for IPC
int		*ft_create_pipes(int no_of_cmds);
// redirect pipes to move data between processes
void	ft_redir_pipes(int *io_fd, int process, int *pipe_fd, int no_of_cmds);
// check if program has here_doc as an argument and return 1 or 0
// it is used instead a flag to incremment counters in other functions
int		ft_is_heredoc(char *argv[]);
// returns naumber of commands i.e how many
//sub-processes the program will execute
int		ft_no_cmd(int argc, char *argv[]);
// process counter - counts process iterations and holds the value inside STATIC
// variable, also update process variable value for other function use
int		ft_process(int *process, int no_of_cmds);
// checks for argument input and either allow
//to continue or terminates the program
int		ft_check_args(int argc, char **argv, char **envp);
#endif
