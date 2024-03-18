/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:48:01 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/25 20:48:01 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/lexer.h"

void	append_arg(t_ast_node *args_node, t_ast_node *arg_node)
{
	t_list	*new_arg;

	if (!args_node)
		return ;
	new_arg = ft_lstnew(arg_node);
	if (!new_arg)
		return ;
	if (!args_node->u_node_data.arg_list)
		args_node->u_node_data.arg_list = new_arg;
	else
		ft_lstadd_back(&args_node->u_node_data.arg_list, new_arg);
}

t_ast_node	*parse_argv(t_list **cur_token)
{
	t_ast_node	*args_node;
	t_ast_node	*arg_node;

	args_node = create_arg_list_node();
	while (*cur_token != NULL && accept_word(*cur_token))
	{
		arg_node = create_file_name_node(
				((t_token *)(*cur_token)->content)->value);
		if (!arg_node)
		{
			return (NULL);
		}
		consume_token(cur_token);
		append_arg(args_node, arg_node);
	}
	return (args_node);
}

t_ast_node	*create_arg_list_node(void)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->node_type = NODE_ARG_LIST;
	node->u_node_data.arg_list = NULL;
	return (node);
}

void	free_arg_list_node(t_ast_node *node)
{
	ft_lstclear(&node->u_node_data.arg_list, free_ast);
}
