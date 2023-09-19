/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjurakho <jjurakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:17:28 by jjurakho          #+#    #+#             */
/*   Updated: 2023/09/19 20:04:36 by jjurakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buf(char *line, int fd) // in case use original version
{
	int		rd;
	char	*buffer;
	char	*temp;
	
	rd = 1;
	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
		{
			free(line);
			line = NULL;
			free(buffer);
			return (NULL);
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
	// printf("str : %s\n", str);
	if (!p)
		return (str);
	i = p - str + 1;
	// printf("line_len: %d\n", i);
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
	// printf("res: %d", *tmp_start);
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
		return (NULL);
	p++;
	line_len = ft_strlen(p);
	// printf("line_len: %d\n", line_len);
	static_update = malloc(sizeof(char) * line_len + 1);
	if (!static_update)
		return (free(line), NULL);
	static_update_start = static_update;
	while (*p)
		*static_update++ = *p++;
	*static_update = '\0';
	// printf("rem: %d\n", *static_update_start);
	free(line);
	return (static_update_start);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*tmp;
	char		*buffer;

	tmp = NULL;
	buffer = NULL;
	if (fd <= 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (fd == -1)
		return (NULL);
	line = read_buf(line, fd);
	tmp = copy_line(line);
	// if (tmp && ft_strchr(line) == NULL)
	// 	return (free(line) tmp);
	tmp = make_next_line(tmp);
	line = make_remainder(line);
	// printf("remainder :%s", line);
	// printf("result :%s", tmp);
	return (tmp);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = open("text.txt", O_RDONLY);
// 	i = 1;
// 	line = get_next_line(fd);
// 	printf("line %d: (%s)", i, line);
// 	while (line)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 		printf("line %d: (%s)", i, line);
// 	}
// 	close(fd);
// 	return (0);
// }

// printf("good!\n");
// gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c get_next_line.h -D BUFFER_SIZE=42  && valgrind -q --leak-check=full -s ./a.out | cat -e 
// cc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c get_next_line.h -fsanitize=address -g3