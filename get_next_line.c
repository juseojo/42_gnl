/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:33:15 by seongjch          #+#    #+#             */
/*   Updated: 2022/05/15 18:31:56 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_chunk(int fd, char	**chunk)
{
	int	i;

	i = 0;
	if (*chunk != NULL)
		free(*chunk);
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

int	append(t_words *list, char *new_word)
{
	t_words	*new_node;
	t_words	*display;

	display = list;
	while (display -> next != NULL)
		display = display -> next;
	if (!(new_node = malloc(sizeof(t_words))))
		return (0);
	new_node -> word = ft_strdup(new_word);
	if (new_node -> word == 0)
		return (0);
	new_node -> next = NULL;
	display -> next = new_node;
	return (1);
}

char	*return_value(t_words **list, char **chunk, int fin)
{
	char	*line;
	int	start;
	int	j;

	j = 0;
	start = 0;
	while (j < fin)
	{
		if (*(*chunk + j) == '\n')
			start = j + 1;
		j++;
	}
	if (fin == start)
		start = 0;
	line = (char *)malloc(sizeof(char) * (fin - start + 1));
	if (!(line))	
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

char	*get_next_line(int fd)
{
	static char	*chunk;
	static int		i;
	static int		ln;
	t_words		*head;

	if (fd < 0)
		return (0);
	head = malloc(sizeof(struct s_words));
	head -> word = 0;
	head -> next = 0;
	if (!(head))
		return (0);
	if (chunk == NULL || *chunk == 0)
	{
		i = 0;
		chunk = 0;
		read_chunk(fd, &chunk);
	}
	while (fd >= 0)
	{
		while (*(chunk + i))
		{
			if (*(chunk + i) == '\n')
			{
				ln = ++i;
				return (return_value(&head, &chunk, i));
			}
			i++;
		}
		if (i == BUFFER_SIZE)
		{
			if (ln > 1)
				append(head, chunk + ln);
			else
				append(head, chunk);
			read_chunk(fd, &chunk);
		}
		else
			return (return_value(&head, &chunk, i));
		i = 0;
	}
	free_words(head);
	return (0);
}
