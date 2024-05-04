/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 14:41:30 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/02/07 19:38:47 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_me(char *buffer, char *str)
{
	if (buffer)
		free(buffer);
	if (str)
		free(str);
	return (NULL);
}

char	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	new_size;

	new_size = (count + 1) * size;
	mem = malloc(new_size);
	if (!mem)
		return (NULL);
	while (new_size--)
		((char *)mem)[new_size] = '\0';
	return (mem);
}

size_t	is_newline(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

size_t	str_len(char *str)
{
	size_t	size;

	size = 0;
	if (!str)
		return (size);
	while (str[size])
		size++;
	return (size);
}

void	ft_strjoin(char *dst, const char *str1, const char *str2, size_t size)
{
	size_t	dst_i;
	size_t	src_i;

	dst_i = 0;
	if (str1)
	{
		src_i = 0;
		while (str1[src_i] && dst_i < size)
		{
			dst[dst_i] = str1[src_i];
			dst_i++;
			src_i++;
		}
	}
	if (str2)
	{
		src_i = 0;
		while (str2[src_i] && dst_i < size)
		{
			dst[dst_i] = str2[src_i];
			dst_i++;
			src_i++;
		}
	}
}
