/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: alexanderkant <akant@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:47:57 by akant         #+#    #+#                 */
/*   Updated: 2020/12/10 16:59:28 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

typedef	struct			s_fd_process
{
	int					exists;
	int					fd;
	int					line_size;
	char				bstr[BUFFER_SIZE + 1];
	int					bindex;
	int					sindex;
}						t_buffer;

int						get_next_line(int fd, char **line);
char					*fix_string_size(char *string, int size, int multiplier);
int						end_of_file(t_buffer *process, char **line);

#endif
