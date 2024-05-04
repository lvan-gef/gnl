/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 14:27:07 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/02/01 22:21:26 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*new_buffer(char *buffer, size_t start_pos)
{
	char	*new_buf;
	size_t	new_len;
	size_t	i;

	if (!buffer)
		return (NULL);
	new_len = str_len(buffer) - start_pos;
	if (new_len <= 0)
		return (free_me(NULL, buffer));
	new_buf = ft_calloc(new_len, sizeof(char));
	if (!new_buf)
		return (free_me(NULL, buffer));
	i = 0;
	while (buffer[start_pos])
	{
		new_buf[i] = buffer[start_pos];
		i++;
		start_pos++;
	}
	free_me(NULL, buffer);
	return (new_buf);
}

static	char	*append_buffer(char *buffer, char *str)
{
	char	*new_buf;
	size_t	new_len;

	if (!buffer && !str)
		return (NULL);
	new_len = str_len(buffer) + str_len(str);
	if (new_len <= 0)
		return (free_me(buffer, str));
	new_buf = ft_calloc(new_len, sizeof(char));
	if (!new_buf)
		return (free_me(buffer, str));
	ft_strjoin(new_buf, buffer, str, new_len);
	free_me(buffer, str);
	return (new_buf);
}

static char	*aline(char *buffer, size_t size)
{
	char	*new_line;

	if (!buffer)
		return (NULL);
	if (size <= 0)
		return (free_me(buffer, NULL));
	new_line = ft_calloc(size, sizeof(char));
	if (!new_line)
		return (NULL);
	ft_strjoin(new_line, buffer, NULL, size);
	return (new_line);
}

static	char	*read_chunk(int fd, char *buffer)
{
	ssize_t	read_size;
	char	*str_chunk;
	size_t	newline;

	newline = 0;
	while (!newline)
	{
		str_chunk = ft_calloc(BUFFER_SIZE, sizeof(char));
		if (!str_chunk)
			return (free_me(buffer, NULL));
		read_size = read(fd, str_chunk, BUFFER_SIZE);
		if (read_size < 0)
			return (free_me(buffer, str_chunk));
		if (read_size == 0)
		{
			free_me(NULL, str_chunk);
			break ;
		}
		newline = is_newline(str_chunk);
		buffer = append_buffer(buffer, str_chunk);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char		*buffer = NULL;
	char			*line;
	size_t			newline_pos;

	buffer = read_chunk(fd, buffer);
	if (!buffer)
		return (NULL);
	newline_pos = is_newline(buffer);
	if (newline_pos)
	{
		line = aline(buffer, newline_pos);
		if (line)
			buffer = new_buffer(buffer, newline_pos);
		else
			buffer = free_me(buffer, NULL);
		return (line);
	}
	line = aline(buffer, str_len(buffer));
	buffer = free_me(buffer, NULL);
	return (line);
}
