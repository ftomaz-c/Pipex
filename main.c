/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:59:06 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/15 16:49:47 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("infile", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("\033[31mError opening the file.\033[0m\n");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		ft_printf("%s", line);
		free(line);
	}
	close(fd);
}

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
