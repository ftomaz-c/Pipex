/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:02:38 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/29 15:05:50 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error1(int argc, char **argv)
{
	int i;

	if (argc < 5)
	{
		perror("Usage: ./pipex file1 cmd1 cmd2 cmd3 ... file2");
		exit(EXIT_FAILURE);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 0)
		{
			perror("Error: Empty argument detected.");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (ft_strncmp(argv[1], "here_doc", 8) != 0)
		access_check(argc, argv);
}

void	access_check(int argc, char **argv)
{
	if (access(argv[1], R_OK) == -1)
	{
		perror("Error: accessing input file");
		exit (EXIT_FAILURE);
	}
	if (access(argv[argc - 1], F_OK) == 0)
	{
		if (access(argv[argc - 1], W_OK) == -1)
		{
			perror("Error: accessing output file");
			exit (EXIT_FAILURE);
		}
	}
}
