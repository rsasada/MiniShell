/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:03:48 by jongykim          #+#    #+#             */
/*   Updated: 2024/03/18 11:03:48 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*realloc_str(char *str, size_t size)
{
	char	*new_str;
	size_t	old_size;

	new_str = malloc(size);
	if (!new_str)
		return (NULL);
	ft_memset(new_str, 0, size);
	if (str != NULL)
	{
		old_size = ft_strlen(str);
		if (old_size > 0)
		{
			if (old_size < size)
				ft_memcpy(new_str, str, old_size);
			else
				ft_memcpy(new_str, str, old_size - 1);
		}
		free(str);
	}
	return (new_str);
}
