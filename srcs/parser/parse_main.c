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

#include "../../include/minishell.h"

void print_token_list(t_list *tokens) {
	while (tokens) {
		t_token *token = (t_token *)tokens->content;
		const char *type_str = "";

		switch (token->type) {
			case TOKEN_WORD:
				type_str = "WORD";
				break;
			case TOKEN_REDIRECT:
				type_str = "REDIRECT";
				break;
			case TOKEN_PIPE:
				type_str = "PIPE";
				break;
			default:
				type_str = "UNKNOWN";
		}

		printf("Token Type: %s, Value: %s\n", type_str, token->value);
		tokens = tokens->next;
	}
}

t_ast_node *ast_parser(t_list **token_list)
{
	t_ast_node	*root;

	if (token_list == NULL || *token_list == NULL)
		return (NULL);
	root = parse_pipeline(token_list);
	return (root);
}

void print_tree(t_ast_node *node, int level) {
    if (node == NULL)
        return;

    for (int i = 0; i < level; ++i) {
        printf("    ");
    }

    switch (node->node_type) {
        case NODE_PIPELINE:
            printf("Pipeline\n");
            print_tree(node->u_node_data.s_pipeline.left, level + 1);
            print_tree(node->u_node_data.s_pipeline.right, level + 1);
            break;
        case NODE_CMD:
            printf("Command\n");
            print_tree(node->u_node_data.s_cmd.simple_cmd, level + 1);
            print_tree(node->u_node_data.s_cmd.redirection, level + 1);
            break;
        case NODE_SIMPLE_CMD:
            printf("Simple Command\n");
            print_tree(node->u_node_data.s_simple_cmd.file_path, level + 1);
            print_tree(node->u_node_data.s_simple_cmd.args, level + 1);
            break;
        case NODE_ARG_LIST:
            printf("Argument List\n");
            t_list *current = node->u_node_data.arg_list;
            while (current != NULL) {
                t_ast_node *arg_node = (t_ast_node *) (current->content);
                if (arg_node != NULL) {
                    for (int i = 0; i < level + 1; ++i) {
                        printf("    ");
                    }
                    if (arg_node->node_type == NODE_FILENAME) {
                        printf("Filename: %s\n", arg_node->u_node_data.file_name_val);
                    }
                }
                current = current->next;
            }
            break;
        case NODE_REDIRECTION:
            printf("Redirection: %s\n", node->u_node_data.s_redirection.op);
            print_tree(node->u_node_data.s_redirection.file_name, level + 1);
            break;
        case NODE_FILENAME:
            printf("Filename: %s\n", node->u_node_data.file_name_val);
            break;
        case NODE_FILEPATH:
            printf("Filepath: %s\n", node->u_node_data.file_path_val);
            break;
        default:
            printf("Unknown Node\n");
    }
}
