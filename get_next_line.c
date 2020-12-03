/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: alexanderkant <akant@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:47:01 by akant         #+#    #+#                 */
/*   Updated: 2020/12/03 18:04:27 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		end_reached(buffer *process, char **line)
{
	if (process->bstr[process->bindex] == '\0')
		return (end_of_file(process, line));
	process->bindex++;
	*line = fix_string_size(*line, process->sindex + 1, 1);
	if (!*line)
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
		if (process->sindex == process->line_size - 1)
		{
			*line = fix_string_size((*line), process->line_size, 2);
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
	int		processint;

	while (1)
	{
		if (process->bindex == BUFFER_SIZE || process->bindex == 0)
		{
			process->bindex = 0;
			bytes_read = read(process->fd, process->bstr, BUFFER_SIZE);
			if (bytes_read < BUFFER_SIZE)
				process->bstr[bytes_read] = '\0';
			if (!bytes_read)
			{
				(*line)[process->sindex] = '\0';
				return (end_of_file(process, line));
			}
			if (bytes_read < 0)
			{
				process->exists = 0;
				return (-1);
			}
		}
		processint = process_line(process, line);
		if (processint)
			return (end_reached(process, line));
		else if (processint == -1)
			return (-1);
	}
}

void	make_process(buffer *process, int fd)
{
	if (!process || process->exists != 1)
	{
		process->fd = fd;
		process->bindex = 0;
		process->exists = 1;
	}
	process->sindex = 0;
	process->line_size = 20;
}

int		get_next_line(int fd, char **line)
{
	static buffer	array[1];
	buffer			*process;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	process = array;
	make_process(process, fd);
	*line = malloc(process->line_size);
	if (!*line)
		return (-1);
	return (line_read(line, process));
}
