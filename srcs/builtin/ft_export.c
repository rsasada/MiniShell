/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:53:36 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/24 16:53:36 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static int	is_valid_arg(char *arg)
{
	int	i;

	if (arg[0] == '#')
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
	}
	return (1);
}

static int	validate_pid(t_app *app, pid_t *pid)
{
	pid_t	*first_pid;

	if (!app || !app->pid_storage || !pid)
		return (0);
	first_pid = (pid_t *)(app->pid_storage->content);
	if (pid != first_pid)
		return (0);
	return (1);
}

static int	process_first_arg(t_app *app, t_list *argv)
{
	char	*first_arg;

	first_arg = ((t_ast_node *) argv->content)->u_node_data.file_name_val;
	if (first_arg || *first_arg == '#')
	{
		print_env(app, 1);
		return (0);
	}
	return (1);
}

static void	process_args(t_list *argv)
{
	t_list	*argv_cur;
	char	*arg;

	argv_cur = argv;
	while (argv_cur)
	{
		arg = ((t_ast_node *)(argv_cur->content))->u_node_data.file_name_val;
		if (!is_valid_arg(arg))
		{
			ft_putstr_fd("push: export: `", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			handling_error("': not a valid identifier", 1);
		}
		argv_cur = argv_cur->next;
	}
}

void	ft_export(t_app *app, t_list *argv, pid_t *pid)
{
	if (!validate_pid(app, pid))
		return ;
	if (!process_first_arg(app, argv))
		return ;
	process_args(argv);
}
