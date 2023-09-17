
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*buff;

	if (!s1 && !s2)
		return (NULL);
	if (s2)
		i = ft_strlen(s1);
	i = 0;
	j = ft_strlen(s2);
	buff = malloc(sizeof(char) * (i + j + 1));
	if (!buff)
		return (free(buff), NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		buff[i] = s1[i];
		i++;
	}
	while (s2[j])
		buff[i++] = s2[j++];
	buff[i] = '\0';
	return (buff);
}

int	index_of(const char *s, char c)
{
	int		i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

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

char	*copy_line(char *line)
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
	return (tmp);
}

int main()
{
	int fd = open("text.txt", O_RDONLY);

	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	close(fd);
}