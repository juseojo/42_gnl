/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:33:54 by seongjch          #+#    #+#             */
/*   Updated: 2022/05/17 06:05:31 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1, int size)
{
	char	*cpy;
	int		len;

	len = size + 1;
	cpy = malloc(len);
	if (!cpy)
		return (0);
	*cpy = 0;
	ft_strlcat(cpy, s1, len, 0);
	return (cpy);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size, size_t dst_len)
{
	size_t	i;

	i = 0;
	while (src[i] && dst_len + i + 1 < size)
	{
		dest[dst_len + i] = src[i];
		i++;
	}
	dest[size - 1] = 0;
	return (i + dst_len);
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

int	append(t_words *list, char *new_word, int size)
{
	t_words	*new_node;
	t_words	*display;

	display = list;
	while (display -> next != NULL)
		display = display -> next;
	new_node = malloc(sizeof(t_words));
	if (!new_node)
		return (0);
	new_node -> word = ft_strdup(new_word, size);
	new_node -> len = size;
	if (new_node -> word == 0)
		return (0);
	new_node -> next = NULL;
	display -> next = new_node;
	return (1);
}
