
char	*make_next_line(char *tmp)
{
	int j;
	int i;
	char *return_line;

	if (!tmp)
		return (NULL);
	i = index_of(tmp, '\n');
	if (i == -1)
		i = ft_strlen(tmp);
	else
		i += 1;
	return_line = malloc(sizeof(char) * i + 1);
	printf("created: %p\n", return_line);
	j = 0;
	while (j <= i && tmp[j])
	{
		return_line[j] = tmp[j];
		j++;
	}
	return_line[j] = '\0';
	return (return_line);
}

char	*make_remainder(char *line)
{
	int		j;
	int		i;
	char	*tmp;

	// printf("line: %s\n", line);
	if (!line)
		return (NULL);
	i = index_of(line, '\n') + 1;
	if (i == -1)
		return (NULL);
	j = 0;
	j = ft_strlen(line) - i;
	if (j <= 0) 
		return (NULL);
	tmp = malloc(sizeof(char) * j + 1);
	printf("created: %p\n", tmp);
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