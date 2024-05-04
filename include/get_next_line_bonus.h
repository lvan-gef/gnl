/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 22:19:11 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/05/05 01:02:08 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// src/get_next_line.c
char	*get_next_line(int fd);

// src/get_next_line_utils.c
char	*free_me(char *buffer, char *str);
char	*ft_calloc(size_t count, size_t size);
size_t	is_newline(char *str);
size_t	str_len(char *str);
void	ft_strjoin(char *dst, const char *str1, const char *str2, size_t size);
#endif
