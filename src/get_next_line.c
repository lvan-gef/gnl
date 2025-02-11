/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 20:31:49 by lvan-gef      #+#    #+#                 */
/*   Updated: 2025/02/11 23:06:23 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/get_next_line.h"

static char *read_chunk(t_gnl *gnl);
static void gnl_free(t_gnl *gnl);
static char *aline(t_gnl *gnl);
static ssize_t find_new_line(t_gnl *gnl);

char *get_next_line(int fd) {
    static t_gnl gnl = {0};
    char *line = NULL;

    if (BUF_SIZE < 1) {
        fprintf(stderr, "BUF_SIZE must be more then 0, got: %d\n", BUF_SIZE);
        errno = EINVAL;
        return line;
    }

    if (fd < 0) {
        fprintf(stderr, "Invalid fd, fd must be 0 or more, got: %d\n", fd);
        errno = EINVAL;
        return line;
    }

    gnl.fd = fd;
    line = read_chunk(&gnl);
    if (errno != 0) {
        return line;
    }

    if (line == NULL) {
        return gnl.buf;
    }

    return line;
}

static char *read_chunk(t_gnl *gnl) {
    if (gnl->buf_cap == 0) {
        gnl->buf = calloc(BUF_SIZE + 1, sizeof(*gnl->buf));
        if (gnl->buf == NULL) {
            perror("buf");
            gnl_free(gnl);
            return NULL;
        } else {
            gnl->buf_cap = BUF_SIZE;
        }
    }

    char *line = NULL;
    while (true) {
        if (gnl->buf_len + BUF_SIZE > gnl->buf_cap) {
            size_t new_cap = gnl->buf_cap + BUF_SIZE;

            char *new_buf = realloc(gnl->buf, new_cap + 1);
            if (new_buf == NULL) {
                perror("realloc buf");
                gnl_free(gnl);
                return NULL;
            }

            free(gnl->buf);
            gnl->buf = new_buf;
            gnl->buf_cap = new_cap;
        }

        ssize_t read_size = read(gnl->fd, gnl->buf + gnl->buf_len, BUF_SIZE);
        if (read_size < 0) {
            perror("read");
            gnl_free(gnl);
            return NULL;
        } else if (read_size == 0) {
            return aline(gnl);  // is wrong if there is no newline
        }

        gnl->buf_len += (size_t)read_size;
        line = aline(gnl);
        if (errno != 0) {
            return line;
        } else if (line) {
            return line;
        }
    }

    return NULL; // should never get here?
}

static void gnl_free(t_gnl *gnl) {
    if (gnl == NULL) {
        return;
    }

    if (gnl->buf) {
        free(gnl->buf);
        gnl->buf = NULL;
    }

    gnl->buf_cap = 0;
    gnl->buf_len = 0;
}

static char *aline(t_gnl *gnl) {
    ssize_t new_line_pos = find_new_line(gnl);

    if (new_line_pos == -1) {
        return NULL;
    }

    // calloc space till newline
    // copy it over from buf to line
    // then move everything after newline over in the buffer to the beginning
    // update buf_len

    return NULL;
}

static ssize_t find_new_line(t_gnl *gnl) {
    ssize_t new_line_pos = -1;
    if (gnl == NULL || gnl->buf) {
        return new_line_pos;
    }

    size_t index = 0;
    while (index < gnl->buf_len && index < gnl->buf_cap &&
           gnl->buf[index] != '\0') {
        if (gnl->buf[index] == '\r') {
            if (index + 1 < gnl->buf_len) {
                if (index + 1 == '\n') {
                    return (ssize_t)index;
                }
            }
        } else if (gnl->buf[index] == '\n') {
            return (ssize_t)index;
        }

        index++;
    }

    return new_line_pos;
}
