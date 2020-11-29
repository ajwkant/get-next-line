/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: alexanderkant <akant@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:47:01 by akant         #+#    #+#                 */
/*   Updated: 2020/11/29 14:39:23 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int		end_reached(buffer *process, char **line)
{
	if (process->bstr[process->bindex] == '\0')
		return (end_of_file(process, line));
	process->bindex++;
	*line = fix_string_size(*line, process->sindex + 1);
	process->line_size = 20;
	if (!*line)
		return (-1);
	// printf("|%s\n", *line);
	return (1);
}

int		process_line(buffer *process, char **line)
{
	while (process->bindex < BUFFER_SIZE &&
		process->bstr[process->bindex] != '\n' &&
		process->bstr[process->bindex] != '\0')
	{
		(*line)[process->sindex] = process->bstr[process->bindex];
		process->bindex++;
		process->sindex++;
		if (process->sindex == process->line_size)
		{
			*line = fix_string_size((*line), 2 * process->line_size);
			if (!*line)
				return (-1);
			process->line_size = 2 * process->line_size;
		}
	}
	if (process->bindex != BUFFER_SIZE)
	{
		(*line)[process->sindex] = '\0';
		return (1);
	}
	return (0);
}

int		line_read(char **line, buffer *process)
{
	int		bytes_read;

	while (1)
	{
		if (process->bindex == BUFFER_SIZE || process->bindex == 0)
		{
			process->bindex = 0;
			bytes_read = read(process->fd, process->bstr, BUFFER_SIZE);
			// printf("->%c", process->bstr[0]);
			if (bytes_read < BUFFER_SIZE)
				process->bstr[bytes_read] = '\0';
			if (!bytes_read)
			{
				(*line)[process->sindex] = '\0';
				return (end_of_file(process, line));
			}
			if (bytes_read < 0)
			{
				free(*line);
				process->exists = 0;
				return (-1);
			}
		}
		if (process_line(process, line))
			return (end_reached(process, line));
	}
}

void	make_process(buffer *process, int fd)
{
	if (process->exists != 1)
	{
		process->fd = fd;
		process->line_size = 20;
		process->bindex = 0;
		process->exists = 1;
	}
}

int		get_next_line(int fd, char **line)
{
	static buffer	array[1];
	buffer			*process;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	process = array;
	make_process(process, fd);
	process->sindex = 0;
	*line = malloc(process->line_size);
	if (!*line)
		return (-1);
	return (line_read(line, process));
}

// int main()
// {
// 	int             fd;
// 	int             i;
// 	int             j;
// 	char    		*line = 0;
// 	char			*lineadress[66];

// 	j = 1;
// 	printf("\n==========================================\n");
// 	printf("========== TEST 1 : The Alphabet =========\n");
// 	printf("==========================================\n\n");

// 	if (!(fd = open("files/alphabet", O_RDONLY)))
// 	{
// 		printf("\nError in open\n");
// 		return (0);
// 	}
// 	while ((i = get_next_line(fd, &line)) > 0)
// 	{
// 		printf("%d |%s\n", i, line);
// 		lineadress[j - 1] = line;
// 		j++;
// 	}
// 	printf("%d |%s\n", i, line);
// 	free(line);
// 	close(fd);

// 	if (i == -1)
// 		printf ("\nError in Fonction - Returned -1\n");
// 	else if (j == 66)
// 		printf("\nRight number of lines\n");
// 	else if (j != 66)
// 		printf("\nNot Good - Wrong Number Of Lines\n");
// 	while (--j > 0)
// 		free(lineadress[j - 1]);
// 	j = 1;

// 	printf("\n==========================================\n");
// 	printf("========= TEST 2 : Empty Lines ===========\n");
// 	printf("==========================================\n\n");

// 	if (!(fd = open("files/empty_lines", O_RDONLY)))
// 	{
// 		printf("\nError in open\n");
// 		return (0);
// 	}
// 	while ((i = get_next_line(fd, &line)) > 0)
// 	{
// 		printf("|%s\n", line);
// 		free(line);
// 		j++;
// 	}
// 	printf("|%s\n", line);
// 	free(line);
// 	close(fd);

// 	if (i == -1)
// 		printf ("\nError in Fonction - Returned -1\n");
// 	else if (j == 9)
// 		printf("\nRight number of lines\n");
// 	else if (j != 9)
// 		printf("\nNot Good - Wrong Number Of Lines\n");
// 	j = 1;
// 	printf("\n==========================================\n");
// 	printf("======== TEST 3 : The Empty File =========\n");
// 	printf("==========================================\n\n");

// 	if (!(fd = open("files/empty_file", O_RDONLY)))
// 	{
// 		printf("\nError in open\n");
// 		return (0);
// 	}
// 	while ((i = get_next_line(fd, &line)) > 0)
// 	{
// 		printf("|%s\n", line);
// 		free(line);
// 		j++;
// 	}
// 	printf("|%s\n", line);
// 	free(line);
// 	close(fd);

// 	if (i == -1)
// 		printf ("\nError in Fonction - Returned -1\n");
// 	else if (j == 1)
// 		printf("\nRight number of lines\n");
// 	else if (j != 1)
// 		printf("\nNot Good - Wrong Number Of Lines\n");
// 	j = 1;
// 	printf("\n==========================================\n");
// 	printf("========= TEST 4 : One New Line ==========\n");
// 	printf("==========================================\n\n");

// 	if (!(fd = open("files/1_newline", O_RDONLY)))
// 	{
// 		printf("\nError in open\n");
// 		return (0);
// 	}
// 	while ((i = get_next_line(fd, &line)) > 0)
// 	{
// 		printf("|%s\n", line);
// 		free(line);
// 		j++;
// 	}
// 	printf("|%s\n", line);
// 	free(line);
// 	close(fd);
// 	printf("NUMBERRRRRR: %d\n", j);

// 	if (i == -1)
// 		printf ("\nError in Fonction - Returned -1\n");
// 	else if (j == 2)
// 		printf("\nRight number of lines\n");
// 	else if (j != 2)
// 		printf("\nNot Good - Wrong Number Of Lines\n");
// 	j = 1;
// 	printf("\n==========================================\n");
// 	printf("========= TEST 5 : Four New Lines ========\n");
// 	printf("==========================================\n\n");

// 	if (!(fd = open("files/4_newlines", O_RDONLY)))
// 	{
// 		printf("\nError in open\n");
// 		return (0);
// 	}
// 	while ((i = get_next_line(fd, &line)) > 0)
// 	{
// 		printf("|%s\n", line);
// 		free(line);
// 		j++;
// 	}
// 	printf("|%s\n", line);
// 	free(line);
// 	close(fd);

// 	if (i == -1)
// 		printf ("\nError in Fonction - Returned -1\n");
// 	else if (j == 5)
// 		printf("\nRight number of lines\n");
// 	else if (j != 5)
// 		printf("\nNot Good - Wrong Number Of Lines\n");
// 	j = 1;
// 	printf("\n==========================================\n");
// 	printf("============== TEST 6 : 42 ===============\n");
// 	printf("==========================================\n\n");

// 	if (!(fd = open("files/41_char", O_RDONLY)))
// 	{
// 		printf("\nError in open\n");
// 		return (0);
// 	}
// 	while ((i = get_next_line(fd, &line)) > 0)
// 	{
// 		printf("|%s\n", line);
// 		free(line);
// 		j++;
// 	}
// 	printf("|%s\n", line);
// 	free(line);
// 	close(fd);
// 	if (!(fd = open("files/42_char", O_RDONLY)))
// 	{
// 		printf("\nError in open\n");
// 		return (0);
// 	}
// 	while ((i = get_next_line(fd, &line)) > 0)
// 	{

// 		printf("|%s\n", line);
// 		free(line);
// 		j++;
// 	}
// 	printf("|%s\n", line);
// 	free(line);
// 	close(fd);
// 	if (!(fd = open("files/43_char", O_RDONLY)))
// 	{
// 		printf("\nError in open\n");
// 		return (0);
// 	}
// 	while ((i = get_next_line(fd, &line)) > 0)
// 	{
// 		printf("|%s\n", line);
// 		free(line);
// 		j++;
// 	}
// 	printf("|%s\n", line);
// 	free(line);
// 	close(fd);

// 	if (i == -1)
// 		printf ("\nError in Fonction - Returned -1\n");
// 	else if (j == 1)
// 		printf("\nRight number of lines\n");
// 	else if (j != 1)
// 		printf("\nNot Good - Wrong Number Of Lines\n");
// 	j = 1;
// 	printf("\n==========================================\n");
// 	printf("============= TEST 7 : Marge =============\n");
// 	printf("==========================================\n\n");

// 	int fd2;

// 	if (!(fd = open("files/half_marge_top", O_RDONLY)))
// 	{
// 		printf("\nError in open\n");
// 		return (0);
// 	}
// 	if (!(fd2 = open("files/half_marge_bottom", O_RDONLY)))
// 	{
// 		printf("\nError in open\n");
// 		return (0);
// 	}
// 	while ((i = get_next_line(fd, &line)) > 0)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 		j++;
// 	}
// 	free(line);
// 	while ((i = get_next_line(fd2, &line)) > 0)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 		j++;
// 	}
// 	printf("%s\n", line);
// 	free(line);
// 	close(fd);
// 	close(fd2);

// 	if (i == -1)
// 		printf ("\nError in Fonction - Returned -1\n");
// 	else if (j == 25)
// 		printf("\nRight number of lines\n");
// 	else if (j != 25)
// 		printf("\nNot Good - Wrong Number Of Lines\n");
// 	j = 1;
// 	printf("\n==========================================\n");
// 	printf("========= TEST 8 : Wrong Input ===========\n");
// 	printf("==========================================\n\n");

// 	if (get_next_line(180, &line) == -1)
// 		printf("Well Done, you return -1 if no FD\n\n");
// 	else
// 		printf("Not Good, you don't return -1 if no FD\n\n");
// 	return (0);
// }

// void
// 	test_fd(char **buffer, char const *filename, int fd)
// {
// 	int	r;

// 	if (fd == STDIN_FILENO)
// 		printf("Reading stdin...\n---\n");
// 	else
// 		printf("Reading %s...\n---\n", filename);

// 	while ((r = get_next_line(fd, buffer)) > 0)
// 	{
// 		printf("%2d-%s\n", r, *buffer);
// 		if (*buffer)
// 		{
// 			free(*buffer);
// 			*buffer = NULL;
// 		}
// 	}

// 	if (r >= 0)
// 		printf("%2d-%s\n---\n", r, *buffer);
// 	else
// 		printf("%2d#error\n---\n", r);

// 	if (*buffer)
// 	{
// 		free(*buffer);
// 		*buffer = NULL;
// 	}
// }
