/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:57:04 by jongykim          #+#    #+#             */
/*   Updated: 2023/05/21 14:06:00 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	s_len;
	char	*result;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen (s);
	result = (char *) malloc (sizeof (char) * (s_len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		result[i] = (char) f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
