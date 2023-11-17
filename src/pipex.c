/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:45:45 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/17 17:32:08 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	parent_process(int fd_outfile, int *fd, char *cmd2, char **envp)
{
	int		status;
	char	**path_list;
	char	**cmd2_args;
	pid_t	child_pid;

	child_pid = waitpid(-1, &status, 0);
	if (child_pid == -1)
	{
		perror("Error: Waiting for child process failed");
		exit(EXIT_FAILURE);
	}
	path_list = get_path_list(envp);
	cmd2_args = get_cmd_args(cmd2);
	dup2(fd_outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd_outfile);
	exec_path(path_list, cmd2_args, envp);
	free_split(cmd2_args);
	free_split(path_list);
	exit(EXIT_FAILURE);
}


void	child_process(int fd_infile, int *fd, char *cmd1, char **envp)
{
	char	**path_list;
	char	**cmd1_args;

	path_list = get_path_list(envp);
	cmd1_args = get_cmd_args(cmd1);
	dup2(fd_infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close (fd_infile);
	exec_path(path_list, cmd1_args, envp);
	free_split(cmd1_args);
	free_split(path_list);
	exit(EXIT_FAILURE);
}

void	pipex(int fd_infile, int fd_outfile, char **argv, char **envp)
{
	int		fd[2];
	pid_t	parent_id;

	if (pipe(fd) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	parent_id = fork();
	if (parent_id == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (parent_id == 0)
		child_process(fd_infile, fd, argv[2], envp);
	else
		parent_process(fd_outfile, fd, argv[3], envp);
}
