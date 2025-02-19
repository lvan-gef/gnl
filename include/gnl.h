/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 20:32:07 by lvan-gef      #+#    #+#                 */
/*   Updated: 2025/02/19 15:44:46 by lvan-gef      ########   odam.nl         */
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

/**
 * @brief Reads a single line from a file descriptor.
 *        A line is defined as a sequence of characters ending with '\n', '\r\n' or EOF.
 *
 * @param fd File descriptor to read from.
 * @return A pointer to the line read including the newline character,
 *         or NULL if the end of file has been reached or an error occurred.
 *         The caller is responsible for freeing the returned string.
 */
char *get_next_line(int fd);
