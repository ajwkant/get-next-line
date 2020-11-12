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
	
	fd = open("test", O_RDONLY);
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
