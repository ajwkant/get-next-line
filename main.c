/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: alexanderkant <alexanderkant@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 16:37:35 by alexanderka   #+#    #+#                 */
/*   Updated: 2020/11/29 14:37:57 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

int		main(void)
{
	char	*line;
	// int		ret;
	int		fd1;
	// int		fd2;
	// int		fd3;
	// int		fd4;

	// line = malloc(sizeof(char *));
	if (!(fd1 = open("test5", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	int i;
	while ((i = get_next_line(fd1, &line)) > 0)
	{
		// printf("%d |%s\n", i, line);
		free(line);
	}
	// printf("%d |%s\n", i, line);
	free(line);
	close(fd1);
}
