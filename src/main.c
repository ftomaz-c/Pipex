/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:59:06 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/29 16:11:26 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd_infile;
	int		fd_outfile;
	int		i;

	error1(argc, argv);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		open_fd_files(&fd_infile, &fd_outfile, argc, argv);
		here_doc(argv[2]);
	}
	else
	{
		i = 2;
		open_fd_files(&fd_infile, &fd_outfile, argc, argv);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
	while (i < argc - 2)
		pipex(argv[i++], envp);
	dup2(fd_outfile, STDOUT_FILENO);
	exec_process(argv[argc - 2], envp);
	close(fd_outfile);
	return (0);
}

void	open_fd_files(int *fd_infile, int *fd_outfile, int argc, char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
		{
			perror("Usage: ./pipex ""here_doc"" LIMITER cmd1 cmd2 ... file");
			exit (EXIT_FAILURE);
		}
		*fd_outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (*fd_outfile == -1)
		{
			perror("Error: opening the file.");
			exit (EXIT_FAILURE);
		}
	}
	else
	{
		*fd_infile = open(argv[1], O_RDONLY);
		*fd_outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (*fd_infile == -1 || *fd_outfile == -1)
		{
			perror("Error: opening the file.");
			exit (EXIT_FAILURE);
		}
	}
}
