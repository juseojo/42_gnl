/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:33:37 by seongjch          #+#    #+#             */
/*   Updated: 2022/05/16 21:03:19 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_words {
	struct s_words	*next;
	char			*word;
}	t_words;

typedef struct s_gnl {
	char	*chunk;
	int		i;
	int		ln;
}	t_gnl;

typedef struct s_cnw {
	char	*line;
	int		len;
}	t_cnw;

typedef struct s_rtn {
	char	*line;
	int		start;
}	t_rtn;

void	free_words(t_words *list);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s1, int size);
int		append(t_words *list, char *new_word, int size);
size_t	ft_strlcat(char *dest, const char *src, size_t dst_len, size_t src_len);
size_t	ft_strlen(const char *s);

#endif
