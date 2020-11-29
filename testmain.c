/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testmain.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alexanderkant <alexanderkant@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 16:37:41 by alexanderka   #+#    #+#                 */
/*   Updated: 2020/11/29 14:13:18 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

int		main(void)
{
// 	while(-1)
// 	{
// 		printf("H");
// 	}
	
	
	// char *buf;
	// int result;
	
	// buf = malloc(20 * sizeof(char));
	// while ((result = read(0, buf, 20)))
	// {
	// 	printf("result: %d, buf: %s\n", result, buf);
	// }
		
	
	int fd;
	static char *buf;
	
	buf = malloc(20 * sizeof(char));
	
	fd = open("test5", O_RDONLY);
	while (read(fd, buf, 20))
	{
		printf("%s,", buf);
	}
	printf("\nFinal buffer: %s\n", buf);
	
	// char	**line;
	// int		fd;

	// line = malloc(2 * sizeof(char *));
	// line[0] = malloc(20 * sizeof(char));
	// // fd = open("test", O_RDONLY);
	// fd = 0;
	// get_next_line(fd, line);
	// printf("%s", *line);
	// free(line[0]);
	// free(line);
}
