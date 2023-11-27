/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:59:06 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/27 18:41:41 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd_infile;
	int		fd_outfile;
	int		i;

	error(argc, argv);
	fd_infile = open(argv[1], O_RDONLY);
	fd_outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_infile == -1 || fd_outfile == -1)
	{
		perror("Error: opening the file.");
		return (1);
	}
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	i = 2;
	while (i < argc - 2)
		pipex(argv[i++], envp);
	dup2(fd_outfile, STDOUT_FILENO);
	exec_process(argv[argc - 2], envp);
	close(fd_outfile);
	return (0);
}
