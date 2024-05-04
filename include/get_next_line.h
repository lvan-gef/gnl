/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 22:19:11 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/05/05 01:29:45 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// src/get_next_line.c
char	*get_next_line(int fd);

// src/get_next_line_utils.c
char	*gnl_free(char *buffer, char *str);
char	*gnl_calloc(size_t count, size_t size);
size_t	gnl_is_newline(const char *str);
size_t	gnl_str_len(const char *str);
void	gnl_strjoin(char *dst, const char *str1, const char *str2, size_t size);
#endif
