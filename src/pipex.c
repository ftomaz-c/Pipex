/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:05:32 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/24 17:47:41 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_process(int fd_input, int fd_output, char *cmd, char **envp)
{
	char	**path_list;
	char	**cmd_args;

	path_list = get_path_list(envp);
	cmd_args = get_cmd_args(cmd);
	printf("Executing command: %s with input: %d and output: %d\n", cmd_args[0], fd_input, fd_output);
	if (fd_input != STDIN_FILENO)
	{
		dup2(fd_input, STDIN_FILENO);
		close(fd_input);
	}
	if (fd_output != STDOUT_FILENO)
	{
		dup2(fd_output, STDOUT_FILENO);
		close(fd_output);
	}
	printf("Executing command: %s with input: %d and output: %d\n", cmd_args[0], STDIN_FILENO, STDOUT_FILENO);
	exec_path(path_list, cmd_args, envp);
	perror("Error in exec_path");
	free_split(cmd_args);
	free_split(path_list);
	exit(EXIT_FAILURE);
}

void free_pipes(int **pipes, int num_cmds)
{
	int i;
	for (i = 0; i < num_cmds - 1; i++)
	{
		free(pipes[i]);
	}
	free(pipes);
}

int	**create_pipes(int fd_infile, int fd_outfile, int num_cmds)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(num_cmds + 1, sizeof(int*));
	i = 0;
	while (i < num_cmds + 1)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (pipe(pipes[i]) == -1 || !pipes)
		{
			perror("Error creating pipes");
			free_pipes(pipes, num_cmds);
			exit(EXIT_FAILURE);
		}
		close (pipes[i][0]);
		close (pipes[i][1]);
		if (i == 0)
			pipes[i][0] = fd_infile;
		else if (i == num_cmds - 1)
			pipes[i][1] = fd_outfile;
		i++;
	}
	return(pipes);
}

void	pipex(int fd_infile, int fd_outfile, char **argv, char **envp)
{
	int		num_cmds;
	int		**pipes;
	pid_t	*child_ids;
	int		i;
	int		status;

	num_cmds = count_cmds(argv);
	pipes = create_pipes(fd_infile, fd_outfile, num_cmds);
	child_ids = ft_calloc(num_cmds + 1, sizeof(pid_t));
	if (!child_ids)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}

	i = 0;
	while (i < num_cmds)
	{
		child_ids[i] = fork();
		printf("After fork for process %d, child_ids[%d]: %d\n", i, i, child_ids[i]);
		if (child_ids[i] == -1)
		{
			perror("Error in child process");
			exit (EXIT_FAILURE);
		}
		else if (child_ids[i] == 0)
		{
			if (i == num_cmds - 1)
			{
				close(pipes[i - 1][1]);
				close(pipes[i][0]);
				exec_process(pipes[i - 1][0], pipes[i][1], argv[i + 2], envp);
			}
			else
			{
				close(pipes[i + 1][0]);
				close(pipes[i][1]);
				exec_process(pipes[i][0], pipes[i + 1][1], argv[i + 2], envp);
			}
			exit(EXIT_SUCCESS);
		}
		i++;
	}

	i = 0;
	while (i < num_cmds)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < num_cmds)
	{
		waitpid(child_ids[i], &status, 0);
		printf("%d: Child process %d terminated with status: %d\n",child_ids[i], i, status);
		i++;
	}
	free_pipes(pipes, num_cmds);
	free(child_ids);
}
