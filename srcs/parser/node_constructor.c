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

t_ast_node	*create_file_path_node(char *file_path)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->node_type = NODE_FILEPATH;
	node->u_node_data.file_path_val = ft_strdup(file_path);
	if (!node->u_node_data.file_path_val)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_ast_node	*create_file_name_node(char *file_path)
{
	t_ast_node	*node;

	if (file_path == NULL)
		return (NULL);
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->node_type = NODE_FILENAME;
	node->u_node_data.file_name_val = ft_strdup(file_path);
	if (!node->u_node_data.file_name_val)
	{
		free(node);
		return (NULL);
	}
	return (node);
}
