/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:38:38 by akant         #+#    #+#                 */
/*   Updated: 2020/11/21 20:20:42 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

int		main(void)
{
	char	**line;
	int		ret;
	int		fd1;
	int		fd2;
	int		fd3;

	line = malloc(sizeof(char *));
	line[0] = malloc(BUFFER_SIZE * sizeof(char));

	fd1= open("test", O_RDONLY);
	fd2 = open("test2", O_RDONLY);
	fd3 = open("test3", O_RDONLY);

	
	while (0 < (ret = get_next_line(fd1, line)))
	{
		printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd1,*line);
	}
	printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd1, *line);

	while (0 < (ret = get_next_line(fd2, line))) 
	{
		printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd2, *line);;
	}
	printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd2, *line); // x
	// // uvw
	// // xyz
	// //

	// // printf("RETURNWAARDE: %d, LINE: %s\n",ret, *line);
	// ret =  get_next_line(fd, line);
	// printf("RETURNWAARDE: %d, LINE: %s\n",ret, *line); // y
	
	// ret = get_next_line(fd, line);
	// printf("RETURNWAARDE: %d, LINE: %s\n",ret, *line); // 
	
	// ret = get_next_line(fd, line);
	// printf("RETURNWAARDE: %d, LINE: %s\n",ret, *line);
	
	// printf("RETURNWAARDE: %d\n",ret);
	free(line[0]);
	free(line);
}
