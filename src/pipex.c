/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:05:32 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/27 18:57:15 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_process(char *cmd, char **envp)
{
	char	**path_list;
	char	**cmd_args;

	path_list = get_path_list(envp);
	cmd_args = get_cmd_args(cmd);
	exec_path(path_list, cmd_args, envp);
	free_split(cmd_args);
	free_split(path_list);
	exit(EXIT_FAILURE);
}

void	pipex(char *argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("Error creating pipes");
		exit(EXIT_FAILURE);
	}
	if ((pid = fork()) == -1)
	{
		perror("Error in child process");
		exit (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec_process(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
