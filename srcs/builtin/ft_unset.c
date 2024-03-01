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

#include "../../include/builtin.h"

void	append_arg(t_ast_node *args_node, t_ast_node *arg_node);

static int	is_valid_arg(char *arg)
{
	char	*a;

	a = arg;
	if (!ft_isalpha(*a) && *a != '_')
		return (0);
	a++;
	while (a && *a != '\0')
	{
		if (!ft_isalnum(*a) && *a != '_')
			return (0);
		a++;
	}
	return (1);
}

void	ft_unset(t_app *app, t_list *argv, pid_t *pid)
{
	pid_t	*first_pid;
	t_list	*argv_cur;
	char	*arg;

	if (!app || !app->pid_storage || !argv || !pid)
		return ;
	first_pid = (pid_t *)(app->pid_storage->content);
	if (pid != first_pid)
		return ;
	argv_cur = argv;
	while (argv_cur)
	{
		arg = ((t_ast_node *)(argv_cur->content))->u_node_data.file_name_val;
		if (!is_valid_arg(arg))
		{
			ft_putstr_fd("push: unset: `", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			handling_error("': not a valid identifier", 1);
		}
		remove_env(&(app->env_lst), arg);
		argv_cur = argv_cur->next;
	}
}
