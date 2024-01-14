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

#include "parser.h"

t_ast_node *ast_parser(t_list **token_list)
{
	t_ast_node	*root;

	if (token_list == NULL)
		return (NULL);//TODO:Error handling
	root = parse_pipeline(token_list);
	if (root == NULL)
		return (NULL);//TODO:Error handling
	return (root);
}

void print_tree(t_ast_node *node, int level) {
    if (node == NULL)
        return;

    // 들여쓰기를 사용하여 레벨을 표시
    for (int i = 0; i < level; ++i) {
        printf("    ");
    }

    // 노드 유형에 따라 출력
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
                t_ast_node *arg_node = (t_ast_node *)(current->content);
                if (arg_node != NULL) {
                    // 들여쓰기
                    for (int i = 0; i < level + 1; ++i) {
                        printf("    ");
                    }
                    // arg_node의 내용 출력 (예: FILENAME 노드)
                    if (arg_node->node_type == NODE_FILENAME) {
                        printf("Filename: %s\n", arg_node->u_node_data.file_name_val);
                    }
                    // 추가적으로 다른 노드 유형에 대한 처리가 필요하다면 여기에 추가
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


int main(void) {

	t_ast_node *root;
	t_list *head = NULL;
	// "ls | grep 'test'"
	t_token token1 = {TOKEN_WORD, "ls"};
	t_token token2 = {TOKEN_PIPE, "|"};
	t_token token3 = {TOKEN_WORD, "grep"};
	t_token token4 = {TOKEN_WORD, "test"};
	t_token token5 = {TOKEN_REDIRECT, ">>"};
	t_token token6 = {TOKEN_WORD, "test.txt"};
	ft_lstadd_back(&head, ft_lstnew(&token1));
	ft_lstadd_back(&head, ft_lstnew(&token2));
	ft_lstadd_back(&head, ft_lstnew(&token3));
	ft_lstadd_back(&head, ft_lstnew(&token4));
	ft_lstadd_back(&head, ft_lstnew(&token5));
	ft_lstadd_back(&head, ft_lstnew(&token6));

	root = ast_parser(&head);
    print_tree(root, 0);
    return (0);
}
