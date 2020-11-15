/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:38:38 by akant         #+#    #+#                 */
/*   Updated: 2020/11/15 17:07:11 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

int		main(void)
{
	char	**line;
	int		fd;
	int		ret;

	line = malloc(sizeof(char *));
	line[0] = malloc(BUFFER_SIZE * sizeof(char));
	fd = open("test", O_RDONLY);
	// fd = 0;
	while (0 < (ret = get_next_line(fd, line)))
	{
		printf("RETURNVALUE: %d, LINE: %s\n",ret, *line);
	}
	printf("RETURNVALUE: %d, LINE: %s\n",ret, *line);
	
	fd = open("test2", O_RDONLY);
	// fd = 0;
	while (0 < (ret = get_next_line(fd, line)))
	{
		printf("RETURNWAARDE: %d, LINE: %s\n",ret, *line);
	}
	printf("RETURNWAARDE: %d, LINE: %s\n",ret, *line);
	fd = open("test3", O_RDONLY);
	ret = get_next_line(fd, line);
	printf("RETURNWAARDE: %d, LINE: %s\n",ret, *line);
	fd = open("test4", O_RDONLY);
	ret =  get_next_line(fd, line);
	printf("RETURNWAARDE: %d, LINE: %s\n",ret, *line);
	// fd = open("test3", O_RDONLY);
	// ret = get_next_line(fd, line);
	// printf("RETURNWAARDE: %d, LINE: %s\n",ret, *line);
	// fd = open("test4", O_RDONLY);
	// ret = get_next_line(fd, line);
	// printf("RETURNWAARDE: %d, LINE: %s\n",ret, *line);
	
	
	// printf("RETURNWAARDE: %d\n",ret);
	free(line[0]);
	free(line);
}
