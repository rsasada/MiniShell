/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:46:59 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/25 20:46:59 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_ast_node	*parse_cmd(t_list **cur_token, int *error_code)
{
	t_ast_node	*simple_cmd;
	t_ast_node	*redirection;

	if (cur_token == NULL || *cur_token == NULL)
		return (NULL);
	simple_cmd = parse_simple_cmd(cur_token);
	redirection = NULL;
	if (*cur_token != NULL && accept_redirect(*cur_token))
		redirection = parse_redirect(cur_token, error_code);
	if (simple_cmd == NULL && redirection == NULL)
		return (NULL);
	return (create_cmd_node(simple_cmd, redirection));
}

t_ast_node	*create_cmd_node(t_ast_node *simple_cmd, t_ast_node *redirection)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->node_type = NODE_CMD;
	node->u_node_data.s_cmd.simple_cmd = simple_cmd;
	node->u_node_data.s_cmd.redirection = redirection;
	return (node);
}

void	free_cmd_node(t_ast_node *node)
{
	free_ast(node->u_node_data.s_cmd.simple_cmd);
	free_ast(node->u_node_data.s_cmd.redirection);
}
