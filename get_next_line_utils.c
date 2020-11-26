/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:59:22 by akant         #+#    #+#                 */
/*   Updated: 2020/11/24 12:19:01 by alexanderka   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fix_string_size(char *string, int size)
{
	char	*newstring;
	int		i;

	newstring = malloc(size);
	if (!newstring)
		return (NULL);
	i = 0;
	while (i < size)
	{
		newstring[i] = string[i];
		i++;
	}
	free(string);
	return (newstring);
}

