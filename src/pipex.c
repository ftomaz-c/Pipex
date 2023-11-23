/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:45:45 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/22 18:01:22 by ftomaz-c         ###   ########.fr       */
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
	ft_printf("Executing command: %s\n", cmd);
	exec_path(path_list, cmd_args, envp);
	perror("Error in exec_process");
	free_split(cmd_args);
	free_split(path_list);
	perror("Error in exec_path");
	exit(EXIT_FAILURE);
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
	if (pipes == NULL || child_ids == NULL)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}
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
	child_ids[0] = fork();
	if (child_ids[0] == -1)
	{
		perror("Error in the first fork");
		exit(EXIT_FAILURE);
	}
	else if (child_ids[0] == 0)
	{
		close(pipes[0][0]);
		ft_printf("child process 0\n");
		exec_process(fd_infile, pipes[0][1], argv[2], envp);
		exit(EXIT_SUCCESS);
	}
	ft_printf("(PID: %d)\n", child_ids[0]);
	i = 1;
	while (i < num_cmds - 1)
	{
		child_ids[i] = fork();
		if (child_ids[i] == -1)
		{
			perror("Error in fork");
			exit(EXIT_FAILURE);
		}
		else if (child_ids[i] == 0)
		{
			ft_printf("child process %d\n", i);
			close(pipes[i - 1][1]);
			close(pipes[i][0]);
			exec_process(pipes[i - 1][0], pipes[i][1], argv[i + 2], envp);
			exit(EXIT_SUCCESS);
		}
		ft_printf("(PID: %d)\n", child_ids[i]);
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
		close(pipes[num_cmds - 2][1]);
		i = 0;
		while (i < num_cmds - 2)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			i++;
		}
		ft_printf("child process %d (PID: %d)\n", num_cmds - 1, child_ids[num_cmds - 1]);
		exec_process(pipes[num_cmds - 2][0], fd_outfile, argv[num_cmds + 1], envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		i = 0;
		while (i < num_cmds)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			pid_t child_pid = waitpid(child_ids[i], NULL, 0);
			if (child_pid == -1)
			{
				perror("Error waiting for child process");
				exit(EXIT_FAILURE);
			}
			ft_printf("waiting for %d (PID: %d)\n", i, child_pid);
			i++;
		}
	}
	ft_printf("out\n");
	free(pipes);
	free(child_ids);
	exit(EXIT_SUCCESS);
}
