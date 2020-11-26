/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eigenmain.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:38:38 by akant         #+#    #+#                 */
/*   Updated: 2020/11/24 14:34:57 by alexanderka   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

int		main(void)
{
	char	*line;
	// int		ret;
	// int		fd1;
	// int		fd2;
	// int		fd3;
	// int		fd4;

	// line = malloc(sizeof(char *));
	line = NULL;

	// fd1 = open("test5", O_RDONLY);
	// fd2 = open("test2", O_RDONLY);
	// fd3 = open("test3", O_RDONLY);
	// fd4 = open("test4", O_RDONLY);
	
	int fd;
	int		result;

	result = 1;
	
	if (!(fd = open("test5", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	int i;
	while (result > 0)
	{
		result = get_next_line(fd, &line);
		if (result != -1)
		{
			my_ft_putstr_fd(line, fd);
			if (result)
				my_ft_putchar_fd('\n', fd);
		}
		free(line);
	}

	
	// while (0 < (ret = get_next_line(fd1, line)))
	// {
	// 	printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd1,*line);
	// }
	// printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd1, *line);

	// while (0 < (ret = get_next_line(fd3, line)))
	// {
	// 	printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd3,*line);
	// }
	// printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd3, *line);

	// while (0 < (ret = get_next_line(fd4, line))) 
	// {
	// 	printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd4, *line);;
	// }
	// printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd4, *line);

	// // printf("RETURNWAARDE: %d, LINE: %s\n",ret, *line);
	// ret =  get_next_line(fd1, line);
	// printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd1, *line);
	// ret =  get_next_line(fd2, line);
	// printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd2, *line);
	// ret = get_next_line(fd1, line);
	// printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd1, *line);
	// while (0 < (ret = get_next_line(fd2, line))) 
	// {
	// 	printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd2, *line);;
	// }
	// printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd2, *line);
	// while (0 < (ret = get_next_line(fd1, line))) 
	// {
	// 	printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd1, *line);;
	// }
	// printf("RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd1, *line);
	
	// printf("FD: %d\n", fd1);
	// ret = get_next_line(fd1, line);
	// printf("	RETURNVALUE: %d, FD: %d, LINE: %s\n",ret, fd1, *line);
	
	// printf("RETURNWAARDE: %d\n",ret);
	// free(line[0]);
	free(line);
}
