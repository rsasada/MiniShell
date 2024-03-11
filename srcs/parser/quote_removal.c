/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   examine_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:17:48 by risasada          #+#    #+#             */
/*   Updated: 2024/03/09 18:17:53 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	remove_quote_helper(char *str)
{
	char	*reader;
	char	*writer;
	char	current_quote;

	reader = str;
	writer = str;
	current_quote = 0;
	while (*reader)
	{
		if ((*reader == '\'' || *reader == '\"') && \
		(current_quote == 0 || current_quote == *reader))
		{
			if (current_quote == *reader)
				current_quote = 0;
			else
				current_quote = *reader;
		}
		else
			*writer++ = *reader;
		reader++;
	}
	*writer = '\0';
}

void	remove_quote(t_list *token)
{
	char	*content;

	while (token != NULL)
	{
		content = ((t_token *) token->content)->value;
		remove_quote_helper(content);
		token = token->next;
	}
}
