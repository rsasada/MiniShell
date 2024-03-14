/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 00:37:34 by jongykim          #+#    #+#             */
/*   Updated: 2024/03/14 20:14:58 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

//void print_tokens(t_list *head);

void	append_cmds(t_list **cmds, t_list *node)
{
	if (!*cmds)
		*cmds = node;
	else
		ft_lstadd_back(cmds, node);
}

void	append_redirections(t_list **redirections, t_list *node)
{
	if (!*redirections)
		*redirections = node;
	else
		ft_lstadd_back(redirections, node);
}

void	combine_and_clear_lists(t_list **cmds, t_list **redirections,
								t_list **all_tokens)
{
	if (*cmds)
		ft_lstadd_back(cmds, *redirections);
	else
		*cmds = *redirections;
	*redirections = NULL;
	if (*all_tokens)
		ft_lstadd_back(all_tokens, *cmds);
	else
		*all_tokens = *cmds;
	*cmds = NULL;
}

void	process_token(t_list **cur, t_list **cmds, t_list **redirections)
{
	t_token	*token;
	t_list	*new_node;

	token = (t_token *)(*cur)->content;
	new_node = ft_lstnew(copy_token(token));
	if (token->type == TOKEN_REDIRECT)
	{
		append_redirections(redirections, new_node);
		if ((*cur)->next && \
		((t_token *)(*cur)->next->content)->type == TOKEN_WORD)
		{
			*cur = (*cur)->next;
			append_redirections(redirections, \
			ft_lstnew(copy_token((t_token *)(*cur)->content)));
		}
	}
	else
		append_cmds(cmds, new_node);
}

void	reorder_tokens(t_list **tokens)
{
	t_list	*cur;
	t_list	*all_tokens;
	t_list	*cmds;
	t_list	*redirections;
	t_token	*token;

	cur = *tokens;
	all_tokens = NULL;
	cmds = NULL;
	redirections = NULL;
	while (cur)
	{
		token = (t_token *) cur->content;
		if (token->type == TOKEN_PIPE)
		{
			combine_and_clear_lists(&cmds, &redirections, &all_tokens);
			append_cmds(&all_tokens, ft_lstnew(copy_token(token)));
		}
		else
			process_token(&cur, &cmds, &redirections);
		cur = cur->next;
	}
	combine_and_clear_lists(&cmds, &redirections, &all_tokens);
	ft_lstclear(tokens, free_token);
	*tokens = all_tokens;
}
