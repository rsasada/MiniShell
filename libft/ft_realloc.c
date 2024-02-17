/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 00:46:20 by jongykim          #+#    #+#             */
/*   Updated: 2024/01/23 00:46:20 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_realloc(void *ptr, size_t size)
{
    char *src;
    char *dst;
    int i;

    src = (char *) ptr;
    dst = (char *) malloc(size);
    if (!dst) {
        return (NULL);
    }
    if (src != NULL) {
        i = 0;
        while (src[i]) {
            dst[i] = src[i];
            i++;
        }
    }
    free(ptr);
    return ((void *) dst);
}