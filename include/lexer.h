/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:23:39 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/20 22:23:39 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum token_type
{
	TOKEN_WORD,
	TOKEN_REDIRECT,
	TOKEN_PIPE,
	TOKEN_EOF
}	t_token_type;

typedef enum quote_state
{
	OUTSIDE_QUOTES,
	INSIDE_SINGLE_QUOTES,
	INSIDE_DOUBLE_QUOTES
}	t_quote_state;

typedef struct s_tokenizer
{
	t_list			*head;
	char			*line;
	t_quote_state	q_state;
	int				is_env;
	size_t			count;
	size_t			i;
}	t_tokenizer;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

t_list	*tokenizer(char *line, int is_env);
void	init_tokenizer(t_tokenizer *t);
t_list	*malloc_token(char *value, t_token_type type);
void	new_token(t_tokenizer *t, t_token_type type);
void	check_quote_error(t_tokenizer *t);
void	delete_token_from_list(t_list **tokens, t_list *to_delete);

void	trim_token(t_list *token);

#endif