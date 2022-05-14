/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjuncho <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:20:27 by seongjuncho       #+#    #+#             */
/*   Updated: 2022/05/14 17:47:08 by seongjuncho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_words {
	struct		s_words *next;
	char	*word;
} t_words;

char	*get_next_line(int fd);
int	read_chunk(int fd, char **chunk);
char	*ft_strdup(const char *s1);
int	append(t_words *list, char *new_word);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);

#endif
