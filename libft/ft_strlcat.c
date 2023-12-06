/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:00:53 by jongykim          #+#    #+#             */
/*   Updated: 2023/05/20 13:07:05 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		dst_len;
	size_t		src_len;
	size_t		i;
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	i = dstsize;
	dst_len = 0;
	src_len = ft_strlen(s);
	while (i && *d)
	{
		dst_len++;
		d++;
		i--;
	}
	if (i == 0)
		return (dst_len + src_len);
	while (*s && i-- - 1 > 0)
		*d++ = *s++;
	*d = '\0';
	return (dst_len + src_len);
}
