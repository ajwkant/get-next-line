/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/18 16:37:26 by akant         #+#    #+#                 */
/*   Updated: 2020/12/18 16:37:27 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char		buffer[1024][BUFFER_SIZE + 1];
	int				bytes;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, buffer[fd], 0))
		return (-1);
	*line = NULL;
	bytes = 1;
	while (bytes)
	{
		if (!ft_strlen(buffer[fd], '\0'))
		{
			bytes = read_line(buffer[fd], fd);
			if (bytes < 0)
				return (-1);
		}
		if (bytes >= 0)
		{
			*line = new_str(*line, buffer[fd]);
			if (!*line)
				return (-1);
			if (buf_to_line(line, buffer[fd]))
				return (1);
		}
	}
	return (0);
}
