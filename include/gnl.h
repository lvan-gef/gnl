/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 20:32:07 by lvan-gef      #+#    #+#                 */
/*   Updated: 2025/02/11 20:32:07 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

typedef struct s_gnl {
    int fd;
    size_t buf_len;
    size_t buf_cap;
    char *buf;
} t_gnl;

char *get_next_line(int fd);
