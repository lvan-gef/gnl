/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/15 00:00:38 by lvan-gef      #+#    #+#                 */
/*   Updated: 2025/02/19 15:34:23 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "../include/gnl_utils.h"

size_t gnl_strlcpy(char *dst, const char *src, size_t size) {
    size_t len = 0;

    while (++len < size && *src) {
        *dst++ = *src++;
    }

    if (len <= size) {
        *dst = 0;
    }

    return len + strlen(src) - 1;
}

size_t gnl_strlcat(char *dst, const char *src, size_t size) {
    size_t len = strlen(dst);

    if (size <= len + 1) {
        return len + strlen(src);
    }

    return len + gnl_strlcpy(dst + len, src, size - len);
}
