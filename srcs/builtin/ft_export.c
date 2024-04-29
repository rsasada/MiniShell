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
		i++;
	}
	return (1);
}

static int	process_first_arg(t_app *app, t_list *argv)
{
	char	*first_arg;

	if (!argv)
	{
		print_env(app, 1);
		return (0);
	}
	first_arg = ((t_ast_node *) argv->content)->u_node_data.file_name_val;
	if (first_arg && *first_arg == '#')
	{
		print_env(app, 1);
		return (0);
	}
	return (1);
}

static void	export_env(t_app *app, char *arg)
{
	size_t	i;
	char	*key;
	char	*value;

	i = 0;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (arg[i] && arg[i] == '=')
	{
		key = ft_substr(arg, 0, i);
		value = ft_substr(arg, i + 1, ft_strlen(arg) - i);
		add_env(&(app->env_lst), key, value);
		free(key);
		free(value);
	}
}

static int	process_args(t_app *app, t_list *argv)
{
	t_list	*argv_cur;
	char	*arg;
	int		status;

	status = 0;
	argv_cur = argv;
	while (argv_cur)
	{
		arg = ((t_ast_node *)(argv_cur->content))->u_node_data.file_name_val;
		if (is_valid_arg(arg))
			export_env(app, arg);
		else
		{
			ft_putstr_fd("push: export: `", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			status = 1;
		}
		argv_cur = argv_cur->next;
	}
	return (status);
}

int	ft_export(t_app *app, t_list *argv)
{
	if (!process_first_arg(app, argv))
		return (BUILTIN_FAILURE);
	if (process_args(app, argv) == 1)
		return (BUILTIN_FAILURE);
	return (BUILTIN_SUCCESS);
}
