/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:59:06 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/16 18:40:38 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int fd_infile, int fd_outfile, char **argv, char **envp)
{
	/* char	fd[2];
	pid_t	parent_id;
	char	*path; */
	char	*path_from_envp;
	int		index;
	char	**path_list;

	index = 0;
	while (envp[index])
	{
		if (!ft_strncmp(envp[index], "PATH=", 5))
			break ;
		index++;
	}
	path_from_envp = ft_substr(envp[index], 0, ft_strlen(envp[index]));
	path_list = ft_split(path_from_envp, ":");
	index = 0;
	while (path_list[index])
	{
		ft_printf("%s\n", path_list[index]);
		index++;
	}
	(void)fd_infile;
	(void)fd_outfile;
	(void)argv;
	/* split = ft_split(path_from_envp, "\n");
	index = 0;
	while(split)
	{
		if (split[index][1] == 'P' && split[index][1] == 'P' )
	}
	pipe(fd);
	parent_id = fork();
	if (parent_id == -1)
		return (perror("ERROR"));
	if (!parent_id)
		child_process(fd_infile, argv[3], path); */
}

int	main(int argc, char **argv, char **envp)
{
	int		fd_infile;
	int		fd_outfile;

	error(argc, argv);
	fd_infile = open(argv[1], O_RDONLY);
	fd_outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 777);
	if (fd_infile == -1 || fd_outfile == -1)
	{
		ft_printf("\033[31mError opening the file.\033[0m\n");
		return (1);
	}
	pipex(fd_infile, fd_outfile, argv, envp);
	close(fd_infile);
	close(fd_outfile);
	return (0);
}
