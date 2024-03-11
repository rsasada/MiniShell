/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:22:28 by risasada          #+#    #+#             */
/*   Updated: 2024/01/28 00:48:05 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

bool	ft_is_pipeline(t_tokenizer *t);
bool	ft_is_redirect(t_tokenizer *t);
bool	ft_is_quote(t_tokenizer *t);
bool	skip_blanks(t_tokenizer *t);

t_list	*tokenizer(char	*line, int is_env)
{
	t_tokenizer	t;

	init_tokenizer(&t);
	t.line = line;
	t.is_env = is_env;
	while (t.line[t.i] != '\0')
	{
		if (skip_blanks(&t))
			continue ;
		if (ft_is_quote(&t))
			continue ;
		if (ft_is_pipeline(&t))
			continue ;
		if (ft_is_redirect(&t))
			continue ;
		t.count ++;
		t.i ++;
	}
	check_quote_error(&t);
	if (t.count != 0)
		new_token(&t, TOKEN_WORD);
	return (t.head);
}

bool	skip_blanks(t_tokenizer *t)
{
	if (t->line[t->i] == ' ' || t->line[t->i] == '	')
	{
		if (t->q_state != OUTSIDE_QUOTES)
			t->count ++;
		else if (t->q_state == OUTSIDE_QUOTES && t->count != 0)
			new_token(t, TOKEN_WORD);
		t->i ++;
		return (true);
	}
	return (false);
}

bool	ft_is_quote(t_tokenizer *t)
{
	if (t->line[t->i] == '\'')
		handle_single_quote(t);
	else if (t->line[t->i] == '\"')
		handle_double_quote(t);
	else
		return (false);
	return (true);
}

bool	ft_is_pipeline(t_tokenizer *t)
{
	if (t->line[t->i] == '|')
	{
		if (t->q_state == OUTSIDE_QUOTES)
		{
			if (t->count != 0)
				new_token(t, TOKEN_WORD);
			t->count ++;
			t->i ++;
			new_token(t, TOKEN_PIPE);
			return (true);
		}
	}
	return (false);
}

bool	ft_is_redirect(t_tokenizer *t)
{
	if (t->q_state == OUTSIDE_QUOTES)
	{
		if (t->line[t->i] == '<' || t->line[t->i] == '>')
		{
			if (t->count != 0)
				new_token(t, TOKEN_REDIRECT);
			if (t->line[t->i] == t->line[t->i + 1])
			{
				t->count += 2;
				t->i += 2;
			}
			else
			{
				t->count ++;
				t->i ++;
			}
			new_token(t, TOKEN_REDIRECT);
			return (true);
		}
	}
	return (false);
}
