/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 20:31:49 by lvan-gef      #+#    #+#                 */
/*   Updated: 2025/02/19 15:45:00 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/gnl.h"
#include "../include/gnl_utils.h"

static char *read_chunk(t_gnl *gnl);
static void gnl_free(t_gnl *gnl);
static char *extract_line(t_gnl *gnl);
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

    if (line == NULL && gnl.buf_len == 0) {
        gnl_free(&gnl);
    }

    return line;
}

static char *read_chunk(t_gnl *gnl) {
    if (gnl->buf_cap == 0) {
        gnl->buf = calloc(BUF_SIZE + 1, sizeof(char));
        if (gnl->buf == NULL) {
            perror("calloc buffer");
            return NULL;
        }
        gnl->buf_cap = BUF_SIZE;
    }

    char *line = extract_line(gnl);
    if (line != NULL || errno != 0) {
        return line;
    }

    while (true) {
        if (gnl->buf_len + BUF_SIZE > gnl->buf_cap) {
            size_t new_cap = gnl->buf_cap + BUF_SIZE;
            char *new_buf = realloc(gnl->buf, new_cap + 1);
            if (new_buf == NULL) {
                perror("realloc buffer");
                gnl_free(gnl);
                return NULL;
            }
            gnl->buf = new_buf;
            gnl->buf_cap = new_cap;
        }

        ssize_t read_size = read(gnl->fd, gnl->buf + gnl->buf_len, BUF_SIZE);
        if (read_size < 0) {
            perror("read");
            gnl_free(gnl);
            return NULL;
        }

        if (read_size == 0) {
            if (gnl->buf_len > 0) {
                line = calloc(gnl->buf_len + 1, sizeof(char));
                if (line == NULL) {
                    perror("calloc line");
                    gnl_free(gnl);
                    return NULL;
                }
                gnl_strlcpy(line, gnl->buf, gnl->buf_len + 1);
                gnl->buf_len = 0;
                return line;
            }
            return NULL;
        }

        gnl->buf_len += (size_t)read_size;
        gnl->buf[gnl->buf_len] = '\0';

        line = extract_line(gnl);
        if (line != NULL || errno != 0) {
            return line;
        }
    }
}

static void gnl_free(t_gnl *gnl) {
    if (gnl == NULL) {
        return;
    }

    if (gnl->buf != NULL) {
        free(gnl->buf);
        gnl->buf = NULL;
    }

    gnl->buf_cap = 0;
    gnl->buf_len = 0;
}

static char *extract_line(t_gnl *gnl) {
    ssize_t nl_pos = find_new_line(gnl);

    if (nl_pos < 0) {
        return NULL;
    }

    char *line = calloc((size_t)nl_pos + 2, sizeof(char));
    if (line == NULL) {
        perror("calloc line");
        errno = ENOMEM;
        return NULL;
    }

    for (ssize_t i = 0; i <= nl_pos; i++) {
        line[i] = gnl->buf[i];
    }
    line[nl_pos + 1] = '\0';

    size_t remaining = gnl->buf_len - ((size_t)nl_pos + 1);
    if (remaining > 0) {
        memmove(gnl->buf, gnl->buf + nl_pos + 1, remaining);
        gnl->buf_len = remaining;
    } else {
        gnl->buf_len = 0;
    }
    gnl->buf[gnl->buf_len] = '\0';

    return line;
}

static ssize_t find_new_line(t_gnl *gnl) {
    if (gnl == NULL || gnl->buf == NULL || gnl->buf_len == 0) {
        return -1;
    }

    for (size_t i = 0; i < gnl->buf_len; i++) {
        if (gnl->buf[i] == '\n') {
            return (ssize_t)i;
        }

        if (gnl->buf[i] == '\r' && i + 1 < gnl->buf_len &&
            gnl->buf[i + 1] == '\n') {
            return (ssize_t)i;
        }
    }

    return -1;
}
