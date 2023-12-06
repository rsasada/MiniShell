/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:42:02 by jongykim          #+#    #+#             */
/*   Updated: 2023/05/20 13:44:52 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*ss;
	char			*save;
	unsigned char	cc;

	ss = (char *) s;
	save = NULL;
	cc = (unsigned char) c;
	if (cc == '\0')
	{
		while (*ss)
			ss++;
		return (ss);
	}
	while (*ss)
	{
		if (*ss == cc)
			save = ss;
		ss++;
	}
	return (save);
}
