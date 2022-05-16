/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:33:54 by seongjch          #+#    #+#             */
/*   Updated: 2022/05/16 14:36:17 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		len;

	len = ft_strlen(s1) + 1;
	cpy = malloc(len);
	*cpy = 0;
	ft_strlcat(cpy, s1, len);
	return (cpy);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	if (size <= dst_len)
		return (src_len + size);
	while (src[i] && dst_len + i + 1 < size)
	{
		dest[dst_len + i] = src[i];
		i++;
	}
	dest[dst_len + i] = 0;
	return (src_len + dst_len);
}

void	free_words(t_words *list)
{
	t_words	*temp;

	temp = list;
	while (temp != NULL)
	{
		list = list -> next;
		if (temp -> word)
			free(temp -> word);
		if (temp)
			free(temp);
		temp = list;
	}
	free(list);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
	{
		count++;
	}
	return (count);
}

int	append(t_words *list, char *new_word)
{
	t_words	*new_node;
	t_words	*display;

	display = list;
	while (display -> next != NULL)
		display = display -> next;
	new_node = malloc(sizeof(t_words));
	new_node -> word = ft_strdup(new_word);
	if (new_node -> word == 0)
		return (0);
	new_node -> next = NULL;
	display -> next = new_node;
	return (1);
}
