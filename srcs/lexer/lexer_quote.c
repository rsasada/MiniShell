/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:55:24 by risasada          #+#    #+#             */
/*   Updated: 2024/03/11 21:55:25 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

bool	ft_is_metacharacter(char c)
{
	return (c && ft_strchr("<> |\t\n", c));
}

void	handle_double_quote(t_tokenizer *t)
{
	t->count ++;
	t->i ++;
	if (t->q_state == INSIDE_DOUBLE_QUOTES)
	{
		if (t->line[t->i] == '\0' || ft_is_metacharacter(t->line[t->i + 1]))
			new_token(t, TOKEN_WORD);
		else
			t->q_state = OUTSIDE_QUOTES;
	}
	else if (t->q_state == OUTSIDE_QUOTES)
		t->q_state = INSIDE_DOUBLE_QUOTES;
}

void	handle_single_quote(t_tokenizer *t)
{
	t->count ++;
	t->i ++;
	if (t->q_state == INSIDE_SINGLE_QUOTES)
	{
		if (t->line[t->i] == '\0' || ft_is_metacharacter(t->line[t->i + 1]))
			new_token(t, TOKEN_WORD);
		else
			t->q_state = OUTSIDE_QUOTES;
	}
	else if (t->q_state == OUTSIDE_QUOTES)
		t->q_state = INSIDE_SINGLE_QUOTES;
}
