/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:47:01 by akant         #+#    #+#                 */
/*   Updated: 2020/11/21 21:09:48 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		end_reached(buffer *buf)
{
	if (buf->bstr[buf->bindex] == '\0')
	{
		free(buf->bstr);
		// free(buf);
		return (0);
	}
	return (1);
}

void	process_line(buffer *process)
{
	while (process->bstr[process->bindex] != '\n' &&
		process->bstr[process->bindex] != '\0')
}

int		line_read(char *line, buffer *process)
{
	unsigned int	bytes_read;

	while (1)
	{
		if (process->bstr[process->bindex] == '\n')
			process->bindex++;
		if (process->bindex == BUFFER_SIZE || process->bindex == 0)
		{
			process->bindex = 0;
			bytes_read = read(process->fd, process->bstr, BUFFER_SIZE);
			if (!bytes_read)
				return (0);
			if (bytes_read < 0)
				return (-1);
		}
		process_line(process);
		
		
		while (process->bindex < BUFFER_SIZE &&
		process->bstr[process->bindex] != '\n' &&
		process->bstr[process->bindex] != '\0')
		{
			// printf("char: |%c|\n", process->bstr[process->bindex]);
			line[process->sindex] = process->bstr[process->bindex];
			process->bindex++;
			process->sindex++;
		}
		if (process->bstr[process->bindex] == '\0' ||
		process->bstr[process->bindex] == '\n')
		{
			printf("Return");
			line[process->sindex] = '\0';
			process->sindex = 0;
			return (end_reached(process));
		}
	}
	if (!bytes_read) // komt ie hier ooit?
	{
		printf("HIER: %s", process->bstr);
		write(1, "1", 1);
		free(process->bstr);
		return (0);
	}
	return (2);
}

int		line_read(char *line, buffer *process)
{
	unsigned int	bytes_read;

	while (process->bindex == BUFFER_SIZE || process->bindex == 0 ||
	process->bstr[process->bindex] == '\n')
	{
		// printf("bindex: %d\n	sindex: %d\n", process->bindex, process->sindex);
		if (process->bstr[process->bindex] == '\n')
			process->bindex++;
		if (process->bindex == BUFFER_SIZE || process->bindex == 0)
		{
			process->bindex = 0;
			process->sindex = 0;
			bytes_read = read(process->fd, process->bstr, BUFFER_SIZE);
			if (!bytes_read)
				return (0);
		}
		if (bytes_read < 0)
			return (-1);
		while (process->bindex < BUFFER_SIZE &&
		process->bstr[process->bindex] != '\n' &&
		process->bstr[process->bindex] != '\0')
		{
			// printf("char: |%c|\n", process->bstr[process->bindex]);
			line[process->sindex] = process->bstr[process->bindex];
			process->bindex++;
			process->sindex++;
		}
		if (process->bstr[process->bindex] == '\0' ||
		process->bstr[process->bindex] == '\n')
		{
			printf("Return");
			line[process->sindex] = '\0';
			process->sindex = 0;
			return (end_reached(process));
		}
	}
	if (!bytes_read) // komt ie hier ooit?
	{
		printf("HIER: %s", process->bstr);
		write(1, "1", 1);
		free(process->bstr);
		return (0);
	}
	return (2);
}

// bstr groter maken wanneer nodig;

void	make_process(buffer *process, int fd)
{
	process->fd = fd;
	process->line_size = 20;
	process->bstr = malloc(BUFFER_SIZE * sizeof(char));
	process->bindex = 0;
	process->sindex = 0;
}

int		get_next_line(int fd, char **line)
{
	static buffer	array[1024];
	buffer			*process;

	if (fd < 0 || !line)
		return (-1);
	process = &array[fd];
	if (!(process->fd))
	{
		make_process(process, fd);
		if (!(process->bstr))
			return (-1);
	}
	return (line_read(*line, process));
}

// Malloc voor line hierin
// Geld van Simona
// free_array functie;