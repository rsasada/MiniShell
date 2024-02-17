/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:45:34 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/12 20:45:34 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstfind(t_list *list, void *value_to_find, size_t size)
{
	while (list != NULL)
	{
		if (ft_memcmp(list->content, value_to_find, size) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}
