/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjurakho <jjurakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:51:35 by jjurakho          #+#    #+#             */
/*   Updated: 2023/09/17 06:34:46 by jjurakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
int		index_of(const char *s, char c);
char	*copy_line(char *line);
char	*ft_strjoin(char *saved, char *buffer);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_strcpy(char *dest, const char *src);

#endif