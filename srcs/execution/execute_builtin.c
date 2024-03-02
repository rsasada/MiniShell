/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:07:00 by jongykim          #+#    #+#             */
/*   Updated: 2024/03/02 18:08:37 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../include/builtin.h"

int	execute_single_builtin_cmd(t_ast_node *ast, t_app *app)
{
	int			stdin_backup;
	int			stdout_backup;
	t_ast_node	*simple_cmd;
	t_ast_node	*redirection;

	if (ast == NULL)
		return (1);
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup < 0 || stdout_backup < 0)
		exit(1);
	process_redirects(ast->u_node_data.s_cmd.redirection);
	builtin_functions(ast->u_node_data.s_cmd.simple_cmd, app);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	return (true);
}

bool	check_builtin_cmd(t_ast_node *file_path)
{
	char	*cmd_name;

	cmd_name = file_path->u_node_data.file_path_val;
	if (ft_strncmp(cmd_name, "echo", 5) == 0
		|| ft_strncmp(cmd_name, "export", 7) == 0
		|| ft_strncmp(cmd_name, "pwd", 4) == 0
		|| ft_strncmp(cmd_name, "cd", 3) == 0
		|| ft_strncmp(cmd_name, "env", 4) == 0
		|| ft_strncmp(cmd_name, "unset", 6) == 0
		|| ft_strncmp(cmd_name, "exit", 5) == 0)
		return (true);
	return (false);
}

int	builtin_functions(t_ast_node *simple_cmd, t_app *app)
{
	t_ast_node	*file_path;
	t_ast_node	*args;

	file_path = simple_cmd->u_node_data.s_simple_cmd.file_path;
	args = simple_cmd->u_node_data.s_simple_cmd.args;
	if (ft_strncmp(file_path->u_node_data.file_path_val, "echo", 5) == 0)
		return (ft_echo(app, args->u_node_data.arg_list));
	else if (ft_strncmp(file_path->u_node_data.file_path_val, "export", 7) == 0)
		return (ft_export(app, args->u_node_data.arg_list));
	else if (ft_strncmp(file_path->u_node_data.file_path_val, "pwd", 4) == 0)
		return (ft_pwd(app, args->u_node_data.arg_list));
	else if (ft_strncmp(file_path->u_node_data.file_path_val, "cd", 3) == 0)
		return (ft_cd(app, args->u_node_data.arg_list));
	else if (ft_strncmp(file_path->u_node_data.file_path_val, "env", 4) == 0)
		return (ft_env(app, args->u_node_data.arg_list));
	else if (ft_strncmp(file_path->u_node_data.file_path_val, "unset", 6) == 0)
		return (ft_unset(app, args->u_node_data.arg_list));
	else if (ft_strncmp(file_path->u_node_data.file_path_val, "exit", 5) == 0)
		return (ft_exit(app, args->u_node_data.arg_list));
	return (1);
}
