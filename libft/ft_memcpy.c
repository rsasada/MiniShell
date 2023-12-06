/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:32:04 by jongykim          #+#    #+#             */
/*   Updated: 2023/05/20 12:47:19 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	const char	*s;
	char		*d;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = dst;
	s = src;
	while (len--)
		*d++ = *s++;
	return (dst);
}
