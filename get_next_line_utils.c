/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:59:22 by akant         #+#    #+#                 */
/*   Updated: 2020/11/14 18:16:40 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

buffer	*look_lst_for_fd(buffer *list, int fd)
{
	buffer	*temp;

	temp = list;
	if (temp)
	{
		// printf("%p, %p\n", temp, temp->next);
		if (temp->fd == fd)
			return (temp);
		// if (temp->next == temp)
		// 	write(1, "X", 1);
		temp = temp->next;
	}
	return (NULL);
}

void	add_last_node(buffer **list, buffer *new_buf)
{
	buffer *temp;

	temp = *list;
	// printf("%p, %p\n", temp, temp->next);
	while (temp)
	{
		// printf("%p, %p\n", temp, temp->next);
		if (temp->next == NULL)
		{
			printf("THIS WENT OK!\n");
			temp->next = new_buf;
			printf("Third: %p\n", new_buf);
			return ;
		}
		temp = temp->next;
	}
}

buffer	*ft_lstlast(buffer *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}