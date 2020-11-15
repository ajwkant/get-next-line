/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:47:01 by akant         #+#    #+#                 */
/*   Updated: 2020/11/15 17:04:21 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	line_clear(char *line)
{
	int	size;

	size = 0;
	while (size < BUFFER_SIZE)
	{
		line[size] = '\0';
		size++;
	}
}

int		end_reached(buffer *buf)
{
	if (buf->bstr[buf->bindex] == '\0')
	{
		free(buf->bstr);
		free(buf);
		return (0);
	}
	return (1);
}

int		line_read(char *line, buffer *buf)
{
	unsigned int	bytes_read;

	while (buf->bindex == BUFFER_SIZE || buf->bindex == 0 ||
	buf->bstr[buf->bindex] == '\n')
	{
		if (buf->bstr[buf->bindex] == '\n')
			buf->bindex++;
		if (buf->bindex == BUFFER_SIZE || buf->bindex == 0)
		{
			buf->bindex = 0;
			buf->sindex = 0;
			bytes_read = read(buf->fd, buf->bstr, BUFFER_SIZE);
		}
		if (bytes_read < 0)
			return (-1);
		while (buf->bindex < BUFFER_SIZE &&
		buf->bstr[buf->bindex] != '\n' &&
		buf->bstr[buf->bindex] != '\0')
		{
			line[buf->sindex] = buf->bstr[buf->bindex];
			buf->bindex++;
			buf->sindex++;
		}
		if (buf->bstr[buf->bindex] == '\0' || buf->bstr[buf->bindex] == '\n')
			return (end_reached(buf));
	}
	if (!bytes_read)
	{
		printf("HIER: %s", buf->bstr);
		write(1, "1", 1);
		free(buf->bstr);
		free(buf);
		return (0);
	}
	return (2);
}

// buffer	*new_fd(int fdes)
// {
// 	buffer	*buf;

// 	buf = malloc(sizeof(buffer));
// 	if (!buf)
// 		return (NULL);
// 	// buf->next = NULL;
// 	buf->fd = fdes;
// 	buf->bstr = malloc(BUFFER_SIZE * sizeof(char));
// 	if (!buf->bstr)
// 		return (NULL);
// 	buf->bindex = 0;
// 	return (buf);
// }

// int		get_next_line(int fd, char **line)
// {
// 	static buffer	**list;
// 	buffer			*buf;

// 	printf("FD: %d\n", fd);
// 	if (fd < 0 || !line) // line nog zelf mallocen
// 		return (-1);
// 	if (!list)
// 	{
// 		list = malloc(sizeof(buffer *));
// 		if (!list)
// 			return (-1);
// 		buf = new_fd(fd);
// 		if (!buf)
// 			return (-1);
// 		*list = buf;
// 		buf->next = NULL;
// 	}
// 	else
// 	{
// 		buf = look_lst_for_fd(*list, fd);
// 		// printf("Begin else%p, %p\n", buf, list);
// 		if (!buf)
// 		{
// 			printf("%p, %p\n", buf, list);
// 			buf = new_fd(fd);
// 			printf("HERE: %p, %p\n", buf, *list);
// 			if (!buf)
// 				return (-1);
// 			write(1, "Y", 1);
// 			buf->next = NULL;
// 			printf("First: %p, %p, %p\n", *list, (*list)->next, buf);
// 			add_last_node(list, buf);
// 			printf("Second: %p, %p\n", *list, (*list)->next);
// 			write(1, "Z", 1);
// 			// printf("%p, %p, %p\n", list, buf, buf->next);
// 		}
// 	}
// 	buf->sindex = 0;
// 	line_clear(*line);
// 	return (line_read(*line, buf));
// }

buffer	**make_list(buffer **list)
{
	list = malloc(sizeof(buffer *));
	return (list);
}

buffer	*make_buf(int fd)
{
	buffer	*buf;

	// printf("THIS IS NODE NUMBER: |%d| for FD number: |%d|\n", i, fd);
	buf = malloc(sizeof(buffer));
	if (!buf)
		return (NULL);
	buf->fd = fd;
	buf->bstr = malloc(BUFFER_SIZE * sizeof(char));
	if (!buf->bstr)
		return (NULL);
	buf->bindex = 0;
	return (buf);
}

int		get_next_line(int fd, char **line)
{
	static buffer	**list;
	buffer			*buf;

	if (fd < 0 || !line)
		return (-1);
	if (!list)
	{
		printf("New list\n");
		if (!(list = make_list(list)))
			return (-1);
		buf = make_buf(fd);
		printf("THIS IS if NODE NUMBER: |%p| for FD number: |%d|\n", buf, fd);
		*list = buf;
	}
	else
	{
		printf("FD: %d\n", fd);
		if (!(buf = look_lst_for_fd(*list, fd)))
		{
			printf("New node\n");
			buf = make_buf(fd);
			printf("THIS IS else NODE NUMBER: |%p| for FD number: |%d|\n", buf, fd);
			printf("%p, %p\n", ft_lstlast(*list), buf);
			ft_lstlast(*list)->next = buf;
			printf("Node added to list\n");
		}
	}
	buf->sindex = 0;
	line_clear(*line);
	return (line_read(*line, buf));
}

// Malloc voor line hierin
// Geld van Simona