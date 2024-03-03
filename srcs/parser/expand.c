/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 00:18:46 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/29 01:33:02 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/lexer.h"

void	replace_tokens(t_list **old, t_list *node_to_change, t_list *new)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*new_last;

	prev = NULL;
	cur = *old;
	while (cur && cur != node_to_change)
	{
		prev = cur;
		cur = cur->next;
	}
	new_last = new;
	while (new_last -> next != NULL)
		new_last = new_last->next;
	new_last->next = node_to_change->next;
	if (prev)
		prev->next = new;
	else
		*old = new;
	ft_lstdelone(node_to_change, free_token);
}

static void	init_variables(int *i, int *len, int *quote_flag, char **result)
{
	*i = 0;
	*len = 0;
	*quote_flag = 0;
	*result = NULL;
}

char	*expand_token_value(t_app *app, const char *value)
{
	char	*result;
	int		i;
	int		len;
	int		quote_flag;

	if (!value)
		return (NULL);
	init_variables(&i, &len, &quote_flag, &result);
	while (value[i] != '\0')
	{
		if (value[i] == '\"')
		{
			toggle_quote(&quote_flag, &i);
			continue ;
		}
		if (value[i] == '$' && (!quote_flag || value[i + 1] == '?'))
			result = expand_env_helper(app, value, &i, &len);
		else
			result = adjust_result(result, value[i], &len);
		i++;
	}
	if (!result)
		result = strdup("");
	return (result);
}

void	replace_new_value(t_list **tokens, t_list **cur, char *new_value)
{
	t_list	*new;
	t_list	*next;

	new = tokenizer(new_value, 1);
	if (new)
	{
		next = (*cur)->next;
		replace_tokens(tokens, *cur, new);
		*cur = next;
	}
}

void	expand_env(t_app *app, t_list **tokens)
{
	t_list	*cur;
	t_token	*token;
	char	*new_value;

	cur = *tokens;
	while (cur != NULL)
	{
		token = (t_token *)(cur->content);
		if (token && token->type == TOKEN_WORD)
		{
			new_value = expand_token_value(app, token->value);
			if (new_value)
			{
				replace_new_value(tokens, &cur, new_value);
				if (*new_value)
					continue ;
			}
		}
		cur = cur->next;
	}
}
