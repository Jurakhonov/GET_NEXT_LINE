/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjurakho <jjurakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:17:28 by jjurakho          #+#    #+#             */
/*   Updated: 2023/09/20 14:43:15 by jjurakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buf(char *line, char *buffer, int fd)
{
	int		rd;
	char	*temp;

	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
		{
			free(line);
			return (free(buffer), NULL);
		}
		if (rd == 0)
			break ;
		buffer[rd] = '\0';
		temp = ft_strjoin(line, buffer);
		if (line)
			free(line);
		line = temp;
		temp = NULL;
		if (ft_strchr(line, '\n'))
			break ;
	}
	free(buffer);
	return (line);
}

char	*make_next_line(char *str)
{
	char	*p;
	int		i;
	char	*tmp;
	char	*tmp_start;
	char	*str_start;

	if (!str)
		return (NULL);
	p = ft_strchr(str, '\n');
	if (!p)
		return (str);
	i = p - str + 1;
	tmp = malloc(sizeof(char) * i + 1);
	tmp_start = tmp;
	str_start = str;
	while (*str)
	{
		*tmp = *str++;
		if (*tmp++ == '\n')
			break ;
	}
	*tmp = '\0';
	free(str_start);
	return (tmp_start);
}

char	*make_remainder(char *line)
{
	char	*p;
	int		line_len;
	char	*static_update;
	char	*static_update_start;

	if (!line)
		return (NULL);
	p = ft_strchr(line, '\n');
	if (!p || (*(p + 1) == '\0'))
		return (free(line), NULL);
	p++;
	line_len = ft_strlen(p);
	static_update = malloc(sizeof(char) * line_len + 1);
	if (!static_update)
		return (free(line), NULL);
	static_update_start = static_update;
	while (*p)
		*static_update++ = *p++;
	*static_update = '\0';
	free(line);
	return (static_update_start);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*tmp;
	char		*buffer;

	tmp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (fd == -1)
		return (NULL);
	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = read_buf(line, buffer, fd);
	tmp = copy_line(line);
	tmp = make_next_line(tmp);
	line = make_remainder(line);
	return (tmp);
}
