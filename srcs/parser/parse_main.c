/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:15:30 by jongykim          #+#    #+#             */
/*   Updated: 2024/01/14 13:15:30 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_ast_node	*ast_parser(t_list **token_list)
{
	t_ast_node	*root;
	int			error_code;

	if (token_list == NULL || *token_list == NULL)
		return (NULL);
	error_code = PARSE_OK;
	root = parse_pipeline(token_list, &error_code);
	if (error_code == SYNTAX_ERROR)
	{
		free_ast(root);
		return (NULL);
	}
	return (root);
}
