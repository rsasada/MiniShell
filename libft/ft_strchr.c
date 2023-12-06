/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:36:53 by jongykim          #+#    #+#             */
/*   Updated: 2023/05/20 13:41:31 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*ss;
	unsigned char	cc;

	ss = (char *) s;
	cc = (unsigned char) c;
	while (*ss)
	{
		if (*ss == cc)
			return (ss);
		ss++;
	}
	if (*ss == cc)
		return (ss);
	return (NULL);
}
