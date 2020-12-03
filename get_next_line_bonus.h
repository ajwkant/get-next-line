/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: alexanderkant <akant@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:47:57 by akant         #+#    #+#                 */
/*   Updated: 2020/12/02 20:03:28 by alexanderka   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# ifndef BUFFER_SIZE

int	BUFFER_SIZE = 20;
# endif

typedef	struct			fd_process
{
	int					exists;
	int					fd; // weghalen
	int					line_size;
	char				bstr[BUFFER_SIZE + 1];
	int					bindex;
	int					sindex;
}						buffer;

int		get_next_line(int fd, char **line);
char	*fix_string_size(char *string, int size, int multiplier);
int		end_of_file(buffer *process, char **line);

#endif
