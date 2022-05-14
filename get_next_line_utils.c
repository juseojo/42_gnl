/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjuncho <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:31:28 by seongjuncho       #+#    #+#             */
/*   Updated: 2022/05/14 17:48:09 by seongjuncho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		len;

	len = ft_strlen(s1) + 1;
	cpy = malloc(len);
	if (cpy == 0)
		return (0);
	ft_strlcpy(cpy, s1, len);
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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (size < 2)
	{
		if (size == 1)
			dest[i] = 0;
		return (j);
	}
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (j);
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

	if (list -> next == NULL)
	{
		if (!(new_node = malloc(sizeof(t_words))))
			return (0);
		new_node -> word = ft_strdup(new_word);
		if (new_node -> word == 0)
			return (0);
		new_node -> next = NULL;
		list -> next = new_node;
	}
	else
	{
		t_words	*display = list;
		while (display -> next != NULL)
			display = display -> next;
		if (!(new_node = malloc(sizeof(t_words))))
			return (0);
		new_node -> word = ft_strdup(new_word);
		if (new_node -> word == 0)
			return (0);
		new_node -> next = NULL;
		display -> next = new_node;
	}
	return (1);
}
