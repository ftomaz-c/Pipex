/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:03:40 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/22 14:25:43 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../src/libft/includes/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

/* error.c */
void	error(int argc, char **argv);
void	access_check(int argc, char **argv);

/* pipex.c */
void	pipex(int fd_infile, int fd_outfile, char **argv, char **envp);
void	exec_process(int fd_input, int fd_output, char *cmd, char **envp);

/* pipex_utils.c */
char	**get_path_list(char **envp);
void	exec_path(char **path_list, char **cmd_args, char **envp);
void	free_split(char **split);
char	**get_cmd_args(char *cmd);
int		count_cmds(char **argv);

#endif
