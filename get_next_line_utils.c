/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:59:22 by akant         #+#    #+#                 */
/*   Updated: 2020/11/26 20:38:00 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fix_string_size(char *string, int size)
{
	char	*newstring;

	newstring = malloc(size);
	if (!newstring)
		return (NULL);
	while (size)
	{
		newstring[size - 1] = string[size - 1];
		size--;
	}
	free(string);
	return (newstring);
}

int		end_of_file(buffer *process, char **line)
{
	*line = fix_string_size(*line, process->sindex + 1);
	process->exists = 0;
	if (!*line)
		return (-1);
	return (0);
}
