/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:11:00 by jongykim          #+#    #+#             */
/*   Updated: 2024/01/14 16:11:00 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	process_redirect(t_list **cur, t_list **prev)
{
	*prev = (*cur)->next;
	*cur = (*cur)->next->next;
}

static void	process_word(t_list **cur, t_list **prev, t_list **head)
{
	if (*prev != NULL)
	{
		(*prev)->next = (*cur)->next;
		(*cur)->next = *head;
		*head = *cur;
	}
}

static void	process_tokens(t_list **head)
{
	t_list	*cur;
	t_list	*prev;

	prev = NULL;
	cur = *head;
	while (cur != NULL && cur->next != NULL)
	{
		if (accept_redirect(cur) && accept_word(cur->next))
			process_redirect(&cur, &prev);
		else if (accept_word(cur))
		{
			process_word(&cur, &prev, head);
			break ;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void	reorder_tokens(t_list **head)
{
	if (head == NULL || *head == NULL)
		return ;
	process_tokens(head);
}
