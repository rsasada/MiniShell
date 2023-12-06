/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:09:47 by jongykim          #+#    #+#             */
/*   Updated: 2023/05/20 19:45:35 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	front;
	size_t	back;
	size_t	i;
	size_t	s_len;

	if (s1 == NULL)
		return (NULL);
	s_len = ft_strlen(s1);
	i = 0;
	front = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		front = (i++) + 1;
	if (front > s_len)
		return (ft_strdup(""));
	back = s_len - 1;
	i = back;
	while (i && s1[i] && ft_strchr(set, s1[i]))
		back = (i--) - 1;
	return (ft_substr(s1, front, (back - front + 1)));
}
