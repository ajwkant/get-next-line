/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:47:01 by akant         #+#    #+#                 */
/*   Updated: 2020/11/08 21:38:42 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	char			*buf;
	unsigned int	bytes_read;
	int				i;

	if (!fd)   //|| !line)
		return (0);
	buf = malloc(BUFFER_SIZE * sizeof(char));
	if (!buf)
		return (-1);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (!bytes_read)
		return (0);
	i = 0;
	while (buf[i] != '\n')
	{
		(*line)[i] = buf[i];
		i++;
	}
	(*line)[i] = buf[i];
	return (1);
}

// Should behave well reading from file and from stdin
// until EOF