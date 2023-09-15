/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjurakho <jjurakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:17:28 by jjurakho          #+#    #+#             */
/*   Updated: 2023/09/15 10:57:43 by jjurakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buf(char *line, char *buffer, int fd)
{
	int		byt_r;

	byt_r = 1;
	while (byt_r > 0)
	{
		byt_r = read(fd, buffer, BUFFER_SIZE);
		if (byt_r == -1)
		{
			line = NULL;
			return (NULL);
		}
		if (!buffer[0] || byt_r == 0)
		{
			line = NULL;
			return (NULL);
		}
		buffer[byt_r] = '\0';
		line = ft_strjoin(line, buffer);
		if (index_of(line, '\n') != -1 && line[0] != '\n')
			break ;
	}
	return (line);
}

char	*make_next_line(char *tmp)
{
	int		j;
	int		i;
	char	*return_line;

	if (!tmp)
		return (NULL);
	i = index_of(tmp, '\n');
	if (i == -1)
		i = ft_strlen(tmp);
	else
		i += 1;
	return_line = malloc(sizeof(char) * i + 1);
	if (!return_line)
		return (NULL);
	j = 0;
	while (j <= i && tmp[j])
	{
		return_line[j] = tmp[j];
		j++;
	}
	return_line[j] = '\0';
	free(tmp);
	return (return_line);
}

char	*make_remainder(char *line)
{
	int		j;
	int		i;
	char	*tmp;

	i = index_of(line, '\n');
	if (i == -1)
		return (NULL);
	i = i + 1;
	j = 0;
	j = ft_strlen(line) - i;
	if (j <= 0) 
		return (NULL);
	tmp = malloc(sizeof(char) * j + 1);
	if (!tmp)
		return (NULL);
	j = 0;
	while (line[i + j])
	{
		tmp[j] = line[i + j];
		j++;
	}
	tmp[j] = '\0';
	free(line);
	return (tmp);
}

char	*line_dup(char *line)
{
	char	*tmp;
	int		i;

	if (!line)
		return (NULL);
	i = ft_strlen(line);
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (free(line), NULL);
	i = 0;
	while (line[i])
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*tmp;
	char		*buffer;

	tmp = NULL;
	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= __INT_MAX__)
		return (NULL);
	if (fd == -1)
		return (NULL);
	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	buffer[0] = '\0';
	if (!buffer)
		return (free(buffer), NULL);
	line = read_buf(line, buffer, fd);
	free(buffer);
	tmp = copy_line(line);
	tmp = make_next_line(tmp);
	line = make_remainder(line);
	return (tmp);
}

int main()
{
	int fd = open("text.txt", O_RDONLY);

	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
}

// printf("good!\n");
// gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c get_next_line.h -D BUFFER_SIZE=42 && valgrind -q --leak-check=full -s ./a.out | cat -e 
// cc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c get_next_line.h -fsanitize=address -g3