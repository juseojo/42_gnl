/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjuncho <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:16:58 by seongjuncho       #+#    #+#             */
/*   Updated: 2022/05/14 17:46:50 by seongjuncho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_chunk(int fd, char	**chunk)
{
	if (!(*chunk = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (0);
	return (read(fd, *chunk, BUFFER_SIZE));
}

char	*connect_words(t_words *list)
{
	t_words *display; 
	char	*line;
	int		line_len;

	line_len = 0;
	display = list -> next;
	while (display != NULL)
	{
		line_len += ft_strlen(display -> word);
		display = display -> next;
	}
	if (!(line = (char *)malloc(sizeof(char) * line_len + 1)))
		return (0);
	display = list -> next;
	while (display != NULL)
	{
		ft_strlcat(line, display -> word, line_len + 1);
		display = display -> next;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*chunk;
	char	*line;
	int		i;
	t_words *head;

	head = malloc(sizeof(struct s_words));
	i = 0;
	if (!chunk)
	{
		if (!read_chunk(fd, &chunk))
			return (0);
	}
	while (*chunk != '\0')
	{
		while (!(*(chunk + i)))
		{
			if (*(chunk + i) == '\n')
			{
				if (!(line = (char *)malloc(sizeof(char) * i + 1)))
					return (0);
				ft_strlcat(line, chunk, i + 1);
				append(head, line);
				chunk += i + 1;
				free(line);
				line = connect_words(head);
				return (line);
			}
		i++;
		}
		append(head, chunk);
		i = 0;
		read_chunk(fd, &chunk);
	}
	return (0);
}
