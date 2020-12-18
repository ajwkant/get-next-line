/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 09:44:49 by akant         #+#    #+#                 */
/*   Updated: 2020/12/18 16:45:45 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str, char delim)
{
	int i;

	i = 0;
	while (str[i] != delim && str[i])
		i++;
	return (i);
}

int		ft_strccpy(char *s1, char *s2, char c)
{
	while (s2 && *s2 != c && *s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
	if (s2 && *s2 == '\n')
		return (1);
	return (0);
}

void	move_buf_forward(char *buf)
{
	int i;

	i = ft_strlen(buf, '\n') + 1;
	if (buf[i - 1] == '\0')
	{
		buf[0] = '\0';
		return ;
	}
	ft_strccpy(buf, buf + i, '\0');
}

char	*new_str(char *s1, char *s2)
{
	int		i;
	char	*string;
	int		s1_len;
	int		s2_len;

	i = 0;
	if (s1)
		s1_len = ft_strlen(s1, '\0');
	else
		s1_len = 0;
	s2_len = ft_strlen(s2, '\n');
	string = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (string == NULL)
		return (NULL);
	ft_strccpy(string, s1, '\0');
	if (s1)
		free(s1);
	return (string);
}
