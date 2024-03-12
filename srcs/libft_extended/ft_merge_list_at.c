/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_list_at.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:06:23 by jongykim          #+#    #+#             */
/*   Updated: 2024/03/04 02:06:23 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_merge_list_at(t_list **first_list, t_list **second_list, \
int position)
{
	t_list	*temp;
	t_list	*to_replace;
	t_list	*second_list_last;
	int		i;

	temp = *first_list;
	i = 0;
	while (i < position && temp != NULL)
	{
		if (i == position - 1)
		{
			to_replace = temp->next;
			second_list_last = *second_list;
			while (second_list_last && second_list_last->next != NULL)
				second_list_last = second_list_last->next;
			temp->next = *second_list;
			if (second_list_last)
				second_list_last->next = to_replace->next;
			ft_lstdelone(to_replace, free_token);
			break ;
		}
		temp = temp->next;
		i++;
	}
}
