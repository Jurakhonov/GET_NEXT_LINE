/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjurakho <jjurakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:19:48 by jjurakho          #+#    #+#             */
/*   Updated: 2023/09/20 17:29:37 by jjurakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
			line[fd] = 0;
			return (free(line), free(buffer), NULL);
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
	return (free(buffer), line);
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
	static char	*line[1024];
	char		*tmp;
	char		*buffer;

	tmp = NULL;
	if (fd >= 1000 || fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (0);
	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line[fd] = read_buf(line[fd], buffer, fd);
	tmp = copy_line(line[fd]);
	tmp = make_next_line(tmp);
	line[fd] = make_remainder(line[fd]);
	return (tmp);
}
