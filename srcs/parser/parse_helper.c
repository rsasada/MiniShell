/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:20:29 by jongykim          #+#    #+#             */
/*   Updated: 2024/01/14 16:20:29 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_expected(t_list *cur_token, t_token_type expected_type)
{
	if (((t_token *) cur_token->content)->type == expected_type)
		return (1);
	else
		return (0);
}

int	accept_pipe(t_list *cur_token)
{
	return (is_expected(cur_token, TOKEN_PIPE));
}

int	accept_redirect(t_list *cur_token)
{
	return (is_expected(cur_token, TOKEN_REDIRECT));
}

int	accept_word(t_list *cur_token)
{
	return (is_expected(cur_token, TOKEN_WORD));
}

void	free_ast(t_ast_node *node)
{
	if (node == NULL)
		return ;
	if (node->node_type == NODE_PIPELINE)
		free_pipeline_node(node);
	else if (node->node_type == NODE_CMD)
		free_cmd_node(node);
	else if (node->node_type == NODE_SIMPLE_CMD)
		free_simple_cmd_node(node);
	else if (node->node_type == NODE_REDIRECTION)
		free_redirection_node(node);
	else if (node->node_type == NODE_ARG_LIST)
		free_arg_list_node(node);
	else if (node->node_type == NODE_FILENAME)
		free(node->u_node_data.file_name_val);
	else if (node->node_type == NODE_FILEPATH)
		free(node->u_node_data.file_path_val);
	free(node);
}
