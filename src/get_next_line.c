/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 20:31:49 by lvan-gef      #+#    #+#                 */
/*   Updated: 2025/02/11 20:31:49 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/get_next_line.h"

static char *read_chunk(t_gnl *gnl);
static void gnl_free(t_gnl *gnl);
static char *new_line(t_gnl *gnl);

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

    while (true) {
        ssize_t read_size = read(gnl->fd, gnl->buf, BUF_SIZE);
        if (read_size < 0) {
            perror("read");
            gnl_free(gnl);
            return NULL;
        } else if (read_size == 0) {
            // return what is in the buffer
        }

        gnl->buf_len += (size_t)read_size;
        new_line(gnl);

        // search for \n or \r\n
        // if not found alloc more space and keep reading
    }
}

static void gnl_free(t_gnl *gnl) {
    if (gnl == NULL) {
        return;
    }

    if (gnl->buf) {
        free(gnl->buf);
        return;
    }
}

static char *new_line(t_gnl *gnl) {
    (void)gnl;

    return NULL;
}
