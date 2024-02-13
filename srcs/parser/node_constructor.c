/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:09:51 by jongykim          #+#    #+#             */
/*   Updated: 2024/01/14 16:10:11 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_node *create_simple_cmd_node(t_ast_node *file_path_node, t_ast_node *arg_list){
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->node_type = NODE_SIMPLE_CMD;
    node->u_node_data.s_simple_cmd.file_path = file_path_node;
    node->u_node_data.s_simple_cmd.args = arg_list;
    return (node);
}

t_ast_node *create_arg_list_node()
{
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if(!node)
        return (NULL);
    node->node_type = NODE_ARG_LIST;
    node->u_node_data.arg_list = NULL;
    return (node);
}

t_ast_node *create_file_path_node(char *file_path)
{
    t_ast_node  *node;

    node = malloc(sizeof(t_ast_node));
    if(!node)
        return (NULL);
    node->node_type = NODE_FILEPATH;
    node->u_node_data.file_path_val = ft_strdup(file_path);
    if (!node->u_node_data.file_path_val) {
        free(node);
        return (NULL);
    }
    return (node);
}

t_ast_node *create_file_name_node(char *file_path) {
    t_ast_node *node;

    if(file_path == NULL)
        return (NULL);
    node = malloc(sizeof(t_ast_node));
    if(!node)
        return (NULL);
    node->node_type = NODE_FILENAME;
    node->u_node_data.file_name_val = ft_strdup(file_path);
    if(!node->u_node_data.file_name_val) {
        free(node);
        return (NULL);
    }
    return (node);
}

t_ast_node *create_redirection_node(char *op, t_ast_node *file_name_node) {
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->node_type = NODE_REDIRECTION;
    node->u_node_data.s_redirection.op = op;
    node->u_node_data.s_redirection.file_name = file_name_node;
    return node;
}

t_ast_node *create_cmd_node(t_ast_node *simple_cmd, t_ast_node *redirection) {
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    node->node_type = NODE_CMD;
    node->u_node_data.s_cmd.simple_cmd = simple_cmd;
    node->u_node_data.s_cmd.redirection = redirection;
    return (node);
}

t_ast_node *create_pipeline_node(t_ast_node *left, t_ast_node *right) {
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    node->node_type = NODE_PIPELINE;
    node->u_node_data.s_pipeline.left = left;
    node->u_node_data.s_pipeline.right = right;
    return (node);
}
