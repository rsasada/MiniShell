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

static void	insert_at_start(t_list **first_l, t_list **second_l)
{
	t_list	*temp;
	t_list	*second_l_last;

	if (!second_l || !*second_l)
		return ;
	temp = (*first_l)->next;
	ft_lstdelone(*first_l, free_token);
	*first_l = *second_l;
	second_l_last = *second_l;
	while (second_l_last && second_l_last ->next != NULL)
		second_l_last = second_l_last->next;
	if (second_l_last)
		second_l_last->next = temp;
}

static void	search_pos(t_list **cur, t_list **prev, int pos)
{
	int	i;

	i = 0;
	*prev = NULL;
	while (i < pos && *cur != NULL)
	{
		*prev = *cur;
		*cur = (*cur)->next;
		i++;
	}
}

static void	merge_list_at_pos(t_list **first_l, t_list **second_l, int pos)
{
	t_list	*temp;
	t_list	*to_replace;
	t_list	*prev;
	t_list	*second_l_last;

	temp = *first_l;
	search_pos(&temp, &prev, pos);
	if (temp == NULL)
		return ;
	to_replace = temp;
	if (prev)
		prev->next = *second_l;
	second_l_last = *second_l;
	while (second_l_last && second_l_last->next != NULL)
		second_l_last = second_l_last->next;
	if (second_l_last)
		second_l_last->next = temp->next;
	ft_lstdelone(to_replace, free_token);
}

void	ft_merge_list_at(t_list **first_l, t_list **second_l, int pos)
{
	if (pos == 0)
		insert_at_start(first_l, second_l);
	else
		merge_list_at_pos(first_l, second_l, pos);
}
