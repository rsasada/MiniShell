/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:47:15 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/25 20:47:15 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_node	*create_simple_cmd_node(t_ast_node *file_path_node, \
t_ast_node *arg_list)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->node_type = NODE_SIMPLE_CMD;
	node->u_node_data.s_simple_cmd.file_path = file_path_node;
	node->u_node_data.s_simple_cmd.args = arg_list;
	return (node);
}

t_ast_node	*parse_simple_cmd(t_list **cur_token)
{
	t_ast_node	*file_path_node;
	t_ast_node	*argv_node;

	if (*cur_token == NULL || !accept_word(*cur_token))
	{
		return (NULL);
	}
	file_path_node = create_file_path_node(
			((t_token *)(*cur_token)->content)->value);
	*cur_token = (*cur_token)->next;
	if (*cur_token != NULL && accept_word(*cur_token))
	{
		argv_node = parse_argv(cur_token);
		if (!argv_node)
		{
			return (NULL);
		}
		return (create_simple_cmd_node(file_path_node, argv_node));
	}
	return (create_simple_cmd_node(file_path_node, NULL));
}

void	free_simple_cmd_node(t_ast_node *node)
{
	free_ast(node->u_node_data.s_simple_cmd.file_path);
	free_ast(node->u_node_data.s_simple_cmd.args);
}
