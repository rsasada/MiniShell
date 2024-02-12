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

char **get_args(t_list *arg_nodes) {
	t_list *cur;
	t_ast_node *node;
	int len;
	char **ret;
	int i;

	len = 0;
	cur = arg_nodes;
	while (cur)
	{
		len++;
		cur = cur->next;
	}
	ret = (char **) malloc(sizeof(char *) * (len + 1));
	if (!ret)
		exit_with_error("malloc");
	cur = arg_nodes;
	i = 0;
	while (cur) {
		node = (t_ast_node *) (cur->content);
		if (node->node_type == NODE_FILENAME) {
			ret[i] = ft_strdup(node->u_node_data.file_name_val);
			if (!ret[i]) {
				while (i > 0) {}
				free(ret[--i]);
				free(ret);
				return (NULL);
			}
			i++;
		}
		cur = cur->next;
	}
	ret[i] = NULL;
	return (ret);
}
