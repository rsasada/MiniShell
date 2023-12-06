/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:06 by jongykim          #+#    #+#             */
/*   Updated: 2023/05/20 13:52:57 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ss;
	unsigned char		cc;

	ss = (unsigned char *) s;
	cc = (unsigned char) c;
	while (n--)
	{
		if (*ss == cc)
			return ((void *) ss);
		ss++;
	}
	return (0);
}
