/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:28:41 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/25 20:28:41 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_ast_node	*parse_pipeline(t_list **cur_token, int *error_code)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*pipe_node;

	if (cur_token == NULL || *cur_token == NULL)
		return (NULL);
	reorder_tokens(cur_token);
	left = parse_cmd(cur_token, error_code);
	if (left == NULL)
		return (NULL);
	if ((*cur_token) != NULL && accept_pipe(*cur_token))
	{
		*cur_token = (*cur_token)->next;
		if (*cur_token == NULL)
			return (print_syntax_error("newline", error_code));
		right = parse_pipeline(cur_token, error_code);
		if (right == NULL)
			return (NULL);
		pipe_node = create_pipeline_node(left, right);
		left = pipe_node;
	}
	return (left);
}

t_ast_node	*create_pipeline_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->node_type = NODE_PIPELINE;
	node->u_node_data.s_pipeline.left = left;
	node->u_node_data.s_pipeline.right = right;
	return (node);
}

void	free_pipeline_node(t_ast_node *node)
{
	free_ast(node->u_node_data.s_pipeline.left);
	free_ast(node->u_node_data.s_pipeline.right);
}
