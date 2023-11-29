/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:03:40 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/29 16:12:14 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../src/libft/includes/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

void	open_fd_files(int *fd_infile, int *fd_outfile, int argc, char **argv);

/* error.c */
void	error1(int argc, char **argv);
void	access_check(int argc, char **argv);

/* pipex.c */
void	pipex(char *argv, char **envp);
void	exec_process(char *cmd, char **envp);
void	here_doc(char *limiter);
void	get_here_doc(char *limiter, int fd);

/* pipex_utils.c */
char	**get_path_list(char **envp);
void	exec_path(char **path_list, char **cmd_args, char **envp);
void	free_split(char **split);
char	**get_cmd_args(char *cmd);
int		count_cmds(char **argv);

#endif
