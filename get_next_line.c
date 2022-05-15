/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:33:15 by seongjch          #+#    #+#             */
/*   Updated: 2022/05/16 03:58:39 by seongjch         ###   ########.fr       */
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
	if (!(line))
		return (0);
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

char	*return_value(t_words **list, char **chunk, int fin)
{
	char	*line;
	int		start;
	int		j;

	j = 0;
	start = 0;
	while (j < fin)
	{
		if (*(*chunk + j) == '\n' && j + 1 != fin)
			start = j + 1;
		j++;
	}
	line = (char *) malloc(sizeof(char) * (fin - start + 1));
	if (!line)
		return (0);
	*line = 0;
	ft_strlcat(line, *chunk + start, fin - start + 1);
	append(*list, line);
	if (*(*chunk + fin) == '\0')
	{
		free(*chunk);
		*chunk = NULL;
		fin = 0;
	}
	free(line);
	line = connect_words(*list);
	free_words(*list);
	if (*line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*gnl_sub(int fd, t_gnl	*var, t_words **head)
{
	while (fd >= 0)
	{
		while (*(var -> chunk + var -> i))
		{
			if (*(var -> chunk + var -> i) == '\n')
			{
				var -> ln = ++(var -> i);
				return (return_value(head, &var -> chunk, var -> i));
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
			return (return_value(head, &var -> chunk, var -> i));
		var -> i = 0;
	}
	free(*head);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_gnl		var;
	t_words	*head;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	head = malloc(sizeof(struct s_words));
	head -> word = 0;
	head -> next = 0;
	if (!(head))
		return (0);
	if (var.chunk == NULL)
	{
		var.i = 0;
		var.chunk = 0;
		var.ln = 0;
		read_chunk(fd, &var.chunk);
	}
	return (gnl_sub(fd, &var, &head));
}
