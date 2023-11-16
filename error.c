/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:02:38 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/16 17:03:03 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("\033[0;31mUsage: ./pipex file1 cmd1 cmd2 file2\a\033[0m\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(argv[1]) == 0 || ft_strlen(argv[2]) == 0
		|| ft_strlen(argv[3]) == 0 || ft_strlen(argv[4]) == 0)
	{
		ft_putstr_fd("Error: Empty argument detected.\n", 2);
		exit(EXIT_FAILURE);
	}
}