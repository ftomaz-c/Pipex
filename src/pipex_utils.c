/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:46:33 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/24 15:58:24 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	count_cmds(char **argv)
{
	int	i;
	int	count;

	i = 2;
	count = 0;
	while (argv[++i])
		count++;
	return (count);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while(split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	exec_path(char **path_list, char **cmd_args, char **envp)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = 0;
	while (path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		execve(cmd_path, cmd_args, envp);
		free(cmd_path);
		i++;
	}
}

char	**get_cmd_args(char *cmd)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, " ");
	if (!cmd_args)
	{
		free_split(cmd_args);
		perror("Error");
		exit(EXIT_FAILURE);
	}
	return(cmd_args);
}

char	**get_path_list(char **envp)
{
	char	*path_from_envp;
	char	**path_list;
	int		index;

	index = 0;
	while (envp[index])
	{
		if (!ft_strncmp(envp[index], "PATH=", 5))
			break ;
		index++;
	}
	path_from_envp = ft_substr(envp[index], 0, ft_strlen(envp[index]));
	path_list = ft_split(path_from_envp, ":");
	if (!path_list)
	{
		free_split(path_list);
		free(path_from_envp);
		perror("Error");
		exit(EXIT_FAILURE);
	}
	free(path_from_envp);
	return (path_list);
}

