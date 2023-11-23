/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:05:32 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/23 18:10:01 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_process(int fd_input, int fd_output, char *cmd, char **envp)
{
	char	**path_list;
	char	**cmd_args;

	path_list = get_path_list(envp);
	cmd_args = get_cmd_args(cmd);
	dup2(fd_input, STDIN_FILENO);
	dup2(fd_output, STDOUT_FILENO);
	exec_path(path_list, cmd_args, envp);
	perror("Error in exec_path");
	free_split(cmd_args);
	free_split(path_list);
	exit(EXIT_FAILURE);
}

void	create_pipes(int num_cmds, int (*pipes)[2])
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("Error creating pipes");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	pipex(int fd_infile, int fd_outfile, char **argv, char **envp)
{
	int		num_cmds;
	int		(*pipes)[2];
	pid_t	*child_ids;
	int		i;

	num_cmds = count_cmds(argv);
	pipes = malloc((num_cmds - 1) * sizeof(*pipes));
	child_ids = malloc(num_cmds * sizeof(pid_t));
	if (!pipes || !child_ids)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}
	create_pipes(num_cmds, pipes);
	child_ids[0] = fork();
	if (child_ids[0] == -1)
	{
		perror("Error in the first child process");
		exit(EXIT_FAILURE);
	}
	else if (child_ids[0] != 0)
	{
		waitpid(child_ids[0], NULL, 0);
		ft_printf("parent process: (PID: %d)\n", child_ids[0]);
	}
	else if (child_ids[0] == 0)
	{
		ft_printf("child process 0: (PID: %d)\n", child_ids[0]);
		close(pipes[0][0]);
		exec_process(fd_infile, pipes[0][1], argv[2], envp);
	}
	close(pipes[0][1]);
	i = 1;
	while (i < num_cmds - 1)
	{
		child_ids[i] = fork();
		if (child_ids[i] == -1)
		{
			perror("Error in the child process");
			ft_printf("no.%d\n", i);
			exit(EXIT_FAILURE);
		}
		else if (child_ids[i] != 0)
		{
			ft_printf("parent process: (PID: %d)\n", child_ids[i]);
			waitpid(child_ids[i], NULL, 0);
		}
		else if (child_ids[i] == 0)
		{
			ft_printf("child process %i: (PID: %d)\n", i, child_ids[i]);
			close(pipes[i - 1][1]);
			close(pipes[i][0]);
			exec_process(pipes[i - 1][0], pipes[i][1], argv[i + 2], envp);
		}
		i++;
	}
	child_ids[num_cmds - 1] = fork();
	if (child_ids[num_cmds - 1] == -1)
	{
		perror("Error in the last fork");
		exit(EXIT_FAILURE);
	}
	else if (child_ids[num_cmds - 1] == 0)
	{
		ft_printf("child process %i: (PID: %d)\n", num_cmds - 1, child_ids[num_cmds - 1]);
		close(pipes[num_cmds - 2][1]);
		exec_process(pipes[num_cmds - 2][0], fd_outfile, argv[num_cmds + 1], envp);
	}

	i = 0;
	while (i < num_cmds - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(child_ids);
	exit(EXIT_SUCCESS);
}
