/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:48:05 by jongykim          #+#    #+#             */
/*   Updated: 2023/05/26 20:04:36 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	if (*needle == '\0')
		return ((char *) haystack);
	needle_len = ft_strlen(needle);
	while (len && *haystack && len >= needle_len)
	{
		i = 0;
		while (haystack[i] == needle[i] && i < needle_len)
			i++;
		if (needle[i] == '\0')
			return ((char *) haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
