/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: alexanderkant <akant@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:47:01 by akant         #+#    #+#                 */
/*   Updated: 2020/11/25 12:22:43 by alexanderka   ########   odam.nl         */
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
	{
		write(1, "X", 1);
		if (process->bstr)
			free(process->bstr);
		write(1, "Y", 1);
		*line = fix_string_size(*line, process->sindex + 1);
		free(process);
		if(!*line)
			return (-1);
		return (0);
	}
	process->bindex++;
	*line = fix_string_size(*line, process->sindex + 1);
	if(!*line)
		return (-1);
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
			if (!bytes_read) // hier nog naar kijken
			{
				process->bstr[process->bindex] = '\0';
				// evt free line
				return (end_reached(process, line));
			}
			if (bytes_read < 0)
			{
				free(process->bstr);
				free(*line);
				return (-1);
			}
		}
		if (process_line(process, line))
			return (end_reached(process, line));
	}
}

buffer	*make_process(buffer *process, int fd)
{
	process = malloc(sizeof(buffer));
	if (!process)
		return (NULL);
	process->fd = fd;
	process->line_size = 20;
	process->bstr = malloc(BUFFER_SIZE * sizeof(char));
	process->bindex = 0;
	return (process);
}

int		get_next_line(int fd, char **line)
{
	static buffer	*process;

	if (fd <= 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!process)
	{
		write(1, "A", 1);
		process = make_process(process, fd);
		if (!(process))
			return (-1);
	}
	process->sindex = 0;
	*line = malloc(process->line_size);
	if (!*line)
		return (-1);
	return (line_read(line, process));
}

void
	test_fd(char **buffer, char const *filename, int fd)
{
	int	r;

	if (fd == STDIN_FILENO)
		printf("Reading stdin...\n---\n");
	else
		printf("Reading %s...\n---\n", filename);

	while ((r = get_next_line(fd, buffer)) > 0)
	{
		printf("%2d-%s\n", r, *buffer);
		if (*buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}

	}

	if (r >= 0)
		printf("%2d-%s\n---\n", r, *buffer);
	else
		printf("%2d#error\n---\n", r);

	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

int
	main(void)
{
	char		*buffer = NULL;
	int			i, fd;
	int			test_count;
	char const	*tests[100] = {
		"tests/simple",
		"tests/empty",
		"tests/empty_one",
		"tests/multi_in_one",
		"tests/many_lines",
		"tests/over_buffer",
		"tests/63_line",
		"tests/63_line_nl",
		"tests/64_line",
		"tests/64_line_nl",
		"tests/65_line",
		"tests/65_line_nl",
		"test/baudelaire.txt",
		"test/large_file.txt",
		"tests/lorem_ipsum",
		//"tests/Mr. Justice Maxell by Edgar Wallace.txt",
		NULL
	};

	test_count = 0;
	while (tests[test_count])
		test_count++;
	printf("**********************\n* BUFFER_SIZE %6d *\n**********************\n", BUFFER_SIZE);
	i = 0;
	while (i < test_count)
	{
		fd = open(tests[i], O_RDONLY);
		test_fd(&buffer, tests[i++], fd);
		close(fd);
	}
	test_fd(&buffer, "Invalid file descriptor", 42);
	test_fd(&buffer, NULL, STDIN_FILENO);
	return (0);
}

// int	main(void)
// {
// 	char		*buffer = NULL;
// 	int			fd, r;

// 	fd = open("testfile", O_RDONLY);

// 	while ((r = get_next_line(fd, &buffer)) > 0)
// 	{
// 		printf("%2d-%s\n", r, buffer);
// 		if (buffer)
// 		{
// 			free(buffer);
// 			buffer = NULL;
// 		}
// 	}
// }
