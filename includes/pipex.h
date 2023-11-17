/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:03:40 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/17 16:11:45 by ftomaz-c         ###   ########.fr       */
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

/* pipex.c */
void	pipex(int fd_infile, int fd_outfile, char **argv, char **envp);
void	child_process(int fd_infile, int *fd, char *cmd1, char **envp);
void	parent_process(int fd_outfile, int *fd, char *cmd2, char **envp);

/* pipex_utils.c */
char	**get_path_list(char **envp);
void	exec_path(char **path_list, char **cmd_args, char **envp);
void	free_split(char **split);
char	**get_cmd_args(char *cmd);

#endif