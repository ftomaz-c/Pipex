/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:02:38 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/17 16:57:53 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error(int argc, char **argv)
{
	if (argc != 5)
	{
		perror("Usage: ./pipex file1 cmd1 cmd2 file2");
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(argv[1]) == 0 || ft_strlen(argv[2]) == 0
		|| ft_strlen(argv[3]) == 0 || ft_strlen(argv[4]) == 0)
	{
		perror("Error: Empty argument detected.");
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], R_OK) == -1)
	{
		perror("Error: accessing input file");
		exit (EXIT_FAILURE);
	}
	if (access(argv[4], F_OK) == 0)
	{
		if (access(argv[4], W_OK) == -1)
		{
			perror("Error: accessing output file");
			exit (EXIT_FAILURE);
		}
	}
}
