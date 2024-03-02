/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 22:45:17 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/25 22:57:45 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	get_list_size(t_list *list)
{
	t_list	*cur;
	int		len;

	len = 0;
	cur = list;
	while (cur)
	{
		len++;
		cur = cur->next;
	}
	return (len);
}

static t_list	*merge_args(t_ast_node *node)
{
	t_list	*simple_cmd;
	t_list	*arg_list;

	simple_cmd = ft_lstnew(node->u_node_data.s_simple_cmd.file_path);
	if (node->u_node_data.s_simple_cmd.args != NULL)
		arg_list = node->u_node_data.s_simple_cmd.args->u_node_data.arg_list;
	else
		arg_list = NULL;
	ft_lstadd_front(&arg_list, simple_cmd);
	return (arg_list);
}

static char	**allocate_args(int len)
{
	char	**ret;

	ret = (char **) malloc(sizeof(char *) * (len + 1));
	if (!ret)
		exit_with_error("malloc");
	ft_memset(ret, 0, sizeof(char *) * (len + 1));
	return (ret);
}

static int	fill_args(char **args, t_list *cur)
{
	int			i;
	t_ast_node	*node;

	i = 0;
	while (cur)
	{
		node = (t_ast_node *) cur->content;
		if (node->node_type == NODE_FILENAME)
			args[i] = ft_strdup(node->u_node_data.file_name_val);
		else if (node->node_type == NODE_FILEPATH)
			args[i] = ft_strdup(node->u_node_data.file_path_val);
		if (!args[i])
			return (i);
		i++;
		cur = cur->next;
	}
	args[i] = NULL;
	return (-1);
}

char	**get_args(t_ast_node *simple_cmd)
{
	t_list		*cur;
	int			len;
	int			failed_index;
	char		**ret;

	cur = merge_args(simple_cmd);
	len = get_list_size(cur);
	ret = allocate_args(len);
	failed_index = fill_args(ret, cur);
	if (failed_index != -1)
	{
		while (failed_index > 0)
			free(ret[--failed_index]);
		free(ret);
		return (NULL);
	}
	return (ret);
}
