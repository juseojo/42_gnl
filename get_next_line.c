/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:33:15 by seongjch          #+#    #+#             */
/*   Updated: 2022/05/17 19:24:03 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_chunk(int fd, char	**chunk)
{
	int	i;

	i = 0;
	if (*chunk != NULL)
	{
		free(*chunk);
		*chunk = 0;
	}
	*chunk = (char *) malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!(*chunk))
		return (0);
	while (i <= BUFFER_SIZE)
	{
		*(*chunk + i) = 0;
		i++;
	}
	return (read(fd, *chunk, BUFFER_SIZE));
}

char	*connect_words(t_words *list, int len)
{
	t_words	*see;
	t_cnw	var;

	var.ex = 0;
	see = list -> next;
	var.line = (char *) malloc(++len);
	if (!var.line)
		return (0);
	see = list -> next;
	while (see != NULL)
	{
		var.ex = ft_strlcat(var.line, see -> word, len, var.ex);
		see = see -> next;
	}
	return (var.line);
}

char	*return_value(t_words **list, t_gnl *var, int start)
{
	char	*line;
	int		fin;

	fin = var->i;
	if (var->i != var->ln)
		var->ln = var->i;
	line = (char *)malloc(fin - start + 1);
	if (!line)
		return (0);
	ft_strlcat(line, var->chunk + start, fin - start + 1, 0);
	append(*list, line, fin - start);
	if (*(var->chunk + fin) == '\0')
		var -> i = 0;
	free(line);
	line = connect_words(*list, var->total_len);
	var->total_len = 0;
	free_words(*list);
	if (*line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*gnl_sub(int fd, t_gnl	*var, t_words **head, int start)
{
	while (1)
	{
		start = var->i;
		while (*(var->chunk + var->i))
		{
			(var -> i)++;
			(var -> total_len)++;
			if (*(var->chunk + var->i - 1) == '\n')
			{
				return (return_value(head, var, start));
			}
		}
		if (var->i == BUFFER_SIZE)
		{
			if (var->ln > 0)
				append(*head, var->chunk + var->ln, var->i - var->ln);
			else
				append(*head, var->chunk, var->i);
			read_chunk(fd, &var->chunk);
		}
		else
			return (return_value(head, var, start));
		var->i = 0;
		var->ln = 0;
	}
}

char	*get_next_line(int fd)
{
	static t_gnl	var;
	t_words			*head;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	head = malloc(sizeof(struct s_words));
	if (!head)
		return (0);
	head -> word = 0;
	head -> next = 0;
	if (var.chunk == NULL)
	{
		var.chunk = 0;
		var.ln = 0;
		var.total_len = 0;
		read_chunk(fd, &var.chunk);
	}
	line = gnl_sub(fd, &var, &head, 0);
	if (var.i == 0)
	{
		free(var.chunk);
		var.chunk = 0;
	}
	return (line);
}
