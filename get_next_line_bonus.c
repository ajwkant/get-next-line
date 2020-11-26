/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:47:01 by akant         #+#    #+#                 */
/*   Updated: 2020/11/24 18:32:32 by alexanderka   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		end_reached(buffer *process, char **line)
{
	if (process->bstr[process->bindex] == '\0')
	{
		write(1, "A", 1);
		if (process->bstr)
			free(process->bstr);
		write(1, "B", 1);
		*line = fix_string_size(*line, process->sindex + 1);
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

void	make_process(buffer *process, int fd)
{
	process->fd = fd;
	process->line_size = 20;
	process->bstr = malloc(BUFFER_SIZE * sizeof(char));
	process->bindex = 0;
}

int		get_next_line(int fd, char **line)
{
	static buffer	array[1024];
	buffer			*process;

	if (fd <= 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	process = &array[fd];
	if (!(process->fd))
	{
		make_process(process, fd);
		if (!(process->bstr))
			return (-1);
	}
	process->sindex = 0;
	*line = malloc(process->line_size);
	if (!*line)
		return (-1);
	return (line_read(line, process));
}

// Geld van Simona
// free_array functie;
