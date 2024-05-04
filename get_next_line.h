/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 22:19:11 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/02/07 20:03:03 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*free_me(char *buffer, char *str);
char	*ft_calloc(size_t count, size_t size);
size_t	is_newline(char *str);
size_t	str_len(char *str);
void	ft_strjoin(char *dst, const char *str1, const char *str2, size_t size);
#endif
