/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 03:35:07 by jongykim          #+#    #+#             */
/*   Updated: 2024/01/28 03:35:07 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_token(void *content)
{
    t_token *token;

    token = (t_token *) content;
    if (token != NULL) {
        free(token->value);
        free(token);
    }
}

//TODO:  add funciton for 2 more lines condition e.g: free_pipeline
void free_ast(t_ast_node *node)
{
    if(node == NULL)
        return;
    if(node->node_type == NODE_PIPELINE)
    {
        free_ast(node->u_node_data.s_pipeline.left);
        free_ast(node->u_node_data.s_pipeline.right);
    }
    else if (node->node_type == NODE_CMD)
    {
        free_ast(node->u_node_data.s_cmd.simple_cmd);
        free_ast(node->u_node_data.s_cmd.redirection);
    }
    else if(node->node_type==NODE_SIMPLE_CMD)
    {
        free_ast(node->u_node_data.s_simple_cmd.file_path);
        free_ast(node->u_node_data.s_simple_cmd.args);
    }
    else if(node->node_type == NODE_REDIRECTION)
    {
        free(node->u_node_data.s_redirection.op);
        free_ast(node->u_node_data.s_redirection.file_name);
    }
    else if (node->node_type == NODE_ARG_LIST)
        ft_lstclear(&node->u_node_data.arg_list, free);
    else if(node->node_type == NODE_FILENAME)
        free(node->u_node_data.file_name_val);
    else if(node->node_type == NODE_FILEPATH)
        free(node->u_node_data.file_path_val);
    free(node);
}

void	free_env(void *env)
{
	t_env	*e;

	if (env != NULL)
	{
		e = (t_env *) env;
		free(e->key);
		free(e->value);
		free(e);
	}
}
