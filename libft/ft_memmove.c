/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:49:04 by jongykim          #+#    #+#             */
/*   Updated: 2023/05/21 17:34:19 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*from;
	unsigned char	*to;

	from = (unsigned char *) src;
	to = (unsigned char *) dst;
	if (from == to || len == 0)
		return (dst);
	if (to > from && (size_t)(to - from) < len)
	{
		while (len--)
			to[len] = from[len];
		return (dst);
	}
	while (len--)
		*to++ = *from++;
	return (dst);
}
