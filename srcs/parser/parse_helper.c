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

int is_expected(t_list *cur_token, t_token_type expected_type) {
    if (((t_token *) cur_token->content)->type == expected_type)
        return (1);
    else
        return (0);
}

int accept_pipe(t_list *cur_token) {
    return (is_expected(cur_token, TOKEN_PIPE));
}

int accept_redirect(t_list *cur_token) {
    return (is_expected(cur_token, TOKEN_REDIRECT));
}

int accept_word(t_list *cur_token) {
    return (is_expected(cur_token, TOKEN_WORD));
}

void free_ast_node(void *node_)
{
    t_ast_node *node;

    node = (t_ast_node *) node_;
    if (node == NULL)
        return;
    if (node->node_type == NODE_PIPELINE) {
        free_ast_node(node->u_node_data.s_pipeline.left);
        free_ast_node(node->u_node_data.s_pipeline.right);
    } else if (node->node_type == NODE_CMD) {
        free_ast_node(node->u_node_data.s_cmd.simple_cmd);
        free_ast_node(node->u_node_data.s_cmd.redirection);
    } else if (node->node_type == NODE_SIMPLE_CMD) {
        free_ast_node(node->u_node_data.s_simple_cmd.file_path);
        free_ast_node(node->u_node_data.s_simple_cmd.args);
    } else if (node->node_type == NODE_REDIRECTION) {
        free(node->u_node_data.s_redirection.op);
        free_ast_node(node->u_node_data.s_redirection.file_name);
    }
    else if (node->node_type == NODE_FILENAME)
        free(node->u_node_data.file_name_val);
    else if (node->node_type == NODE_FILEPATH)
        free(node->u_node_data.file_path_val);
    else if (node->node_type == NODE_ARG_LIST)
        ft_lstclear(&(node->u_node_data.arg_list), &free_ast_node);
    free(node);
}