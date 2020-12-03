/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: alexanderkant <akant@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:47:57 by akant         #+#    #+#                 */
/*   Updated: 2020/12/03 16:35:43 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_process
{
	int		exists;
	int		fd;
	int		line_size;
	char	bstr[BUFFER_SIZE + 1];
	int		bindex;
	int		sindex;
}				buffer;

int		get_next_line(int fd, char **line);
char	*fix_string_size(char *string, int size, int multiplier);
int		end_of_file(buffer *process, char **line);

#endif
