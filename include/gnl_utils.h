/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl_utils.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/15 00:01:54 by lvan-gef      #+#    #+#                 */
/*   Updated: 2025/02/19 15:34:43 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>

size_t gnl_strlcpy(char *dst, const char *src, size_t size);
size_t gnl_strlcat(char *dst, const char *src, size_t size);
