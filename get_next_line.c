/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 09:32:35 by akant         #+#    #+#                 */
/*   Updated: 2020/12/18 16:36:51 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		buf_to_line(char **line, char *buffer)
{
	int		start_i;
	int		newline_found;

	start_i = ft_strlen(*line, '\0');
	newline_found = ft_strccpy(*line + start_i, buffer, '\n');
	move_buf_forward(buffer);
	return (newline_found);
}

int		read_line(char *buffer, int fd)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (-1);
	else if (bytes_read == 0)
		return (0);
	buffer[bytes_read] = '\0';
	return (bytes_read);
}

int		get_next_line(int fd, char **line)
{
	static char		buffer[BUFFER_SIZE + 1];
	int				bytes;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, buffer, 0))
		return (-1);
	*line = NULL;
	bytes = 1;
	while (bytes)
	{
		if (!ft_strlen(buffer, '\0'))
		{
			bytes = read_line(buffer, fd);
			if (bytes < 0)
				return (-1);
		}
		if (bytes >= 0)
		{
			*line = new_str(*line, buffer);
			if (!*line)
				return (-1);
			if (buf_to_line(line, buffer))
				return (1);
		}
	}
	return (0);
}
