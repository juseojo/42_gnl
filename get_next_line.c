/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:33:15 by seongjch          #+#    #+#             */
/*   Updated: 2022/05/16 17:24:46 by seongjch         ###   ########.fr       */
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
	while (i <= BUFFER_SIZE)
	{
		*(*chunk + i) = 0;
		i++;
	}
	return (read(fd, *chunk, BUFFER_SIZE));
}

char	*connect_words(t_words *list)
{
	t_words	*display;
	char	*line;
	int		line_len;

	line_len = 0;
	display = list -> next;
	while (display != NULL)
	{
		line_len += ft_strlen(display -> word);
		display = display -> next;
	}
	line = (char *) malloc(sizeof(char) * line_len + 1);
	*line = 0;
	display = list -> next;
	while (display != NULL)
	{
		ft_strlcat(line, display -> word, line_len + 1);
		display = display -> next;
	}
	line[line_len] = 0;
	return (line);
}

char	*return_value(t_words **list, char **chunk, int start, int *fin)
{
	t_rtn	var;

	var.line = (char *)malloc(sizeof(char) * (*fin - start + 1));
	*var.line = 0;
	ft_strlcat(var.line, *chunk + start, *fin - start + 1);
	append(*list, var.line);
	if (*(*chunk + *fin) == '\0')
		*fin = 0;
	free(var.line);
	var.line = connect_words(*list);
	free_words(*list);
	if (*var.line == '\0')
	{
		free(var.line);
		return (NULL);
	}
	return (var.line);
}

char	*gnl_sub(int fd, t_gnl	*var, t_words **head, int start)
{
	while (1)
	{
		start = var -> i;
		while (*(var -> chunk + var -> i))
		{
			if (*(var -> chunk + var -> i) == '\n')
			{
				var -> ln = ++(var -> i);
				return (return_value(head, &var -> chunk, start, &var -> i));
			}
			(var -> i)++;
		}
		if (var -> i == BUFFER_SIZE)
		{
			if (var -> ln > 0)
				append(*head, var -> chunk + var -> ln);
			else
				append(*head, var -> chunk);
			read_chunk(fd, &var -> chunk);
		}
		else
			return (return_value(head, &var -> chunk, start, &var -> i));
		var -> i = 0;
		var -> ln = 0;
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
	head -> word = 0;
	head -> next = 0;
	if (var.chunk == NULL)
	{
		var.chunk = 0;
		var.ln = 0;
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
