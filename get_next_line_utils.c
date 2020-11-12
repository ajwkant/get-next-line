/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:59:22 by akant         #+#    #+#                 */
/*   Updated: 2020/11/10 22:36:23 by alexanderka   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

buffer	*look_lst_for_fd(buffer *list, int fd)
{
	buffer	*temp;

	temp = list;
	if (temp)
	{
		printf("%p, %p\n", temp, temp->next);
		if (temp->fd == fd)
			return (temp);
		if (temp->next == temp)
			write(1, "X", 1);
		temp = temp->next;
	}
	return (NULL);
}

void	add_last_node(buffer *list, buffer *new_buf)
{
	while (list)
	{
		if (list->next == NULL)
		{
			list->next = new_buf;
			return;
		}
		list = list->next;
	}
}

char	*memalloc(size_t nitems, size_t size)
{
	char	*ptr;
	unsigned int		i;

	i = 0;
	ptr = malloc(nitems * size);
	if (!ptr)
		return (NULL);
	
	while (i < nitems)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}
