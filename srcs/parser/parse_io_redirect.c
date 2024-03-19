/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:47:47 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/25 20:49:46 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/lexer.h"

t_ast_node	*parse_io_redirect(t_list **cur_token, int *error_code)
{
	t_token		*token;
	char		*op;
	t_ast_node	*file_name_node;

	if (*cur_token == NULL)
		return (NULL);
	token = (t_token *)(*cur_token)->content;
	if (token->type != TOKEN_REDIRECT)
		return (NULL);
	op = ft_strdup(token->value);
	consume_token(cur_token);
	if (*cur_token == NULL)
		return (print_syntax_error("newline", error_code));
	else if (!accept_word(*cur_token))
		return (print_syntax_error(\
				((t_token *)(*cur_token)->content)->value, error_code));
	if (ft_strncmp(op, "<<", 3) == 0)
		file_name_node = parse_here_doc(cur_token);
	else
		file_name_node = create_file_name_node(
				((t_token *)(*cur_token)->content)->value);
	if (!file_name_node)
		return (NULL);
	consume_token(cur_token);
	return (create_redirection_node(op, file_name_node));
}
