/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus_utils.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alexanderkant <akant@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:59:22 by akant         #+#    #+#                 */
/*   Updated: 2020/12/03 11:50:31 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fix_string_size(char *string, int size, int multiplier)
{
	char	*newstring;

	newstring = malloc(size * multiplier);
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
	*line = fix_string_size(*line, process->sindex + 1, 1);
	process->exists = 0;
	if (!*line)
		return (-1);
	return (0);
}
