/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjurakho <jjurakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:01:18 by jjurakho          #+#    #+#             */
/*   Updated: 2023/09/15 08:38:35 by jjurakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		printf("created: %p\n", s1);
		s1[0] = '\0';
	}
	if (s2 == NULL)
		return (NULL);	
	buff = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 2);
	printf("created: %p\n", buff);
	if (!buff)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[j])
		buff[i++] = s1[j++];
	j = 0;
	while (s2[j])
		buff[i++] = s2[j++];
	buff[i] = '\0';
	printf("remove: %p\n", s1);
	free(s1);
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

void	*ft_memcpy(void *dest, const void *src, int n)
{
	unsigned char	*new_dest;
	unsigned char	*new_src;
	int				i;

	if (!dest && !src)
		return (0);
	new_dest = dest;
	new_src = (unsigned char *)src;
	i = 0;
	while (i++ < n)
		*new_dest++ = *new_src++;
	return (dest);
}

char	*ft_strdup(char *str)
{
	int		n;
	char	*res;

	if (!str)
		return (NULL);
	n = (int)(ft_strlen(str) + 1);
	res = NULL;
	res = (char *)malloc(n);
	printf("created dup: %p\n", res);
	if (res == NULL)
		return (0);
	ft_memcpy(res, str, n);
	return (res);
}
