/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:38:38 by akant         #+#    #+#                 */
/*   Updated: 2020/11/08 21:52:35 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

int		main(void)
{
	char	**line;
	int		fd;

	line = malloc(2 * sizeof(char *));
	line[0] = malloc(BUFFER_SIZE * sizeof(char));
	fd = open("test", O_RDONLY);
	get_next_line(fd, line);
	printf("%s", *line);
}
