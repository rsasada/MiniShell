/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:47:33 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/25 20:47:33 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_node	*parse_redirect(t_list **cur_token, int *error_code)
{
	t_ast_node	*io_redirect;
	t_ast_node	*redirect;

	if (*cur_token == NULL)
		return (NULL);
	io_redirect = parse_io_redirect(cur_token, error_code);
	if (!io_redirect)
		return (NULL);
	if (*cur_token && accept_redirect(*cur_token))
	{
		redirect = parse_redirect(cur_token, error_code);
		if (!redirect)
		{
			return (NULL);
		}
		return (create_pipeline_node(io_redirect, redirect));
	}
	return (io_redirect);
}

t_ast_node	*create_redirection_node(char *op, t_ast_node *file_name_node)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->node_type = NODE_REDIRECTION;
	node->u_node_data.s_redirection.op = op;
	node->u_node_data.s_redirection.file_name = file_name_node;
	return (node);
}

void	free_redirection_node(t_ast_node *node)
{
	free(node->u_node_data.s_redirection.op);
	free_ast(node->u_node_data.s_redirection.file_name);
}
