/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:26:40 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/12 18:26:40 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int get_list_size(t_list *list) {
	t_list *cur;
	int len;

	len = 0;
	cur = list;
	while (cur) {
		len++;
		cur = cur->next;
	}
	return (len);
}

t_list *merge_args(t_ast_node *node) {
	t_list *simple_cmd;
	t_list *arg_list;

	simple_cmd = ft_lstnew(node->u_node_data.s_simple_cmd.file_path);
	if (node->u_node_data.s_simple_cmd.args != NULL)
		arg_list = node->u_node_data.s_simple_cmd.args->u_node_data.arg_list;
	else
		arg_list = NULL;
	ft_lstadd_front(&arg_list, simple_cmd);
	return (arg_list);
}

char **get_args(t_ast_node *simple_cmd) {
	t_list *cur;
	t_ast_node *node;
	int len;
	char **ret;
	int i;

	cur = merge_args(simple_cmd);
	len = get_list_size(cur);
	ret = (char **) malloc(sizeof(char *) * (len + 1));
	if (ret == NULL)
		exit_with_error("malloc");
	i = 0;
	while (cur != NULL) {
		node = (t_ast_node *) cur->content;
		if (node->node_type == NODE_FILENAME)
			ret[i] = ft_strdup(node->u_node_data.file_name_val);
		else if (node->node_type == NODE_FILEPATH)
			ret[i] = ft_strdup(node->u_node_data.file_path_val);
		if (!ret[i])
		{
			while (i > 0)
				free(ret[--i]);
			free(ret);
			return (NULL);
		}
		i++;
		cur = cur->next;
	}
	ret[i] = NULL;
	return (ret);
}