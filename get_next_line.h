/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:47:57 by akant         #+#    #+#                 */
/*   Updated: 2020/11/10 22:36:04 by alexanderka   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

#ifndef BUFFER_SIZE
	int BUFFER_SIZE = 20;
#endif

typedef struct fd_process
{
	int					fd;
	char				*bstr;
	int					bindex;
	int					sindex;
	struct fd_process	*next;
} buffer;

int		get_next_line(int fd, char **line);
buffer	*look_lst_for_fd(buffer *list, int fd);
void	add_last_node(buffer *list, buffer *new_buf);
char	*memalloc(size_t nitems, size_t size);

#endif
