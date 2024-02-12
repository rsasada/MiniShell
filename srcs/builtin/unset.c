/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:02:27 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/12 17:02:27 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_unset(t_app *app, t_list *args, pid_t *pid) {
	pid_t *first_pid;
	t_list *cur_arg;
	char *arg;

	first_pid = (pid_t *) (app->pid_storage->content);
	if (!args || pid != first_pid)
		return;
	cur_arg = args;
	while (cur_arg) {
		arg = ((t_ast_node *)(cur_arg->content))->u_node_data.file_name_val;
		if(find_env(app->env_lst, arg)) {
			ft_lstdelone();
		}


		cur_arg = cur_arg->next;
	}


}