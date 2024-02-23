/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:20:38 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/17 18:20:38 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	new_token(t_tokenizer *t, t_token_type type)
{
	size_t	start;
	char	*value;
	t_list	*new;

	start = t->i - t->count;
	value = ft_substr(t->line, start, t->count);
	if (value == NULL)
		exit(1);
	if (t->is_env)
		type = TOKEN_WORD;
	new = malloc_token(value, type);
	ft_lstadd_back(&t->head, new);
	t->count = 0;
	t->q_state = OUTSIDE_QUOTES;
	return ;
}

t_list	*malloc_token(char *value, t_token_type type)
{
	t_list	*n_list;
	t_token	*n_token;

	n_token = malloc(sizeof(t_token));
	if (n_token == NULL)
		exit(1);
	n_token->value = value;
	n_token->type = type;
	n_list = ft_lstnew(n_token);
	if (n_list == NULL)
		exit(1);
	return (n_list);
}

void	init_tokenizer(t_tokenizer *t)
{
	if (t == NULL)
		return ;
	t->i = 0;
	t->count = 0;
	t->q_state = OUTSIDE_QUOTES;
	t->head = NULL;
	return ;
}

void	check_quote_error(t_tokenizer *t)
{
	if (t->q_state == INSIDE_DOUBLE_QUOTES)
		exit_with_error("minishell: syntax error near Unclosed single quote");
	else if (t->q_state == INSIDE_SINGLE_QUOTES)
		exit_with_error("minishell: syntax error near Unclosed double quote");
	return ;
}
