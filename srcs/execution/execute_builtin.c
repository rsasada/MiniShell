/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:29:50 by risasada          #+#    #+#             */
/*   Updated: 2024/03/07 19:29:54 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../include/builtin.h"

int	execute_single_builtin_cmd(t_ast_node *ast, t_app *app)
{
	int			stdin_backup;
	int			stdout_backup;
	int			redirect_flag;

	if (ast == NULL)
		return (0);
	redirect_flag = 0;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup < 0 || stdout_backup < 0)
		exit(1);
	process_redirects(ast->u_node_data.s_cmd.redirection, &redirect_flag);
	if (redirect_flag == 0)
		g_signal = builtin_functions(ast->u_node_data.s_cmd.simple_cmd, app);
	else
		g_signal = 1;
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	return (1);
}

bool	check_builtin_cmd(t_ast_node *simple_cmd)
{
	t_ast_node	*file_path;
	char		*cmd_name;

	if (simple_cmd == NULL)
		return (false);
	file_path = simple_cmd->u_node_data.s_simple_cmd.file_path;
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
	t_ast_node	*argv;
	t_list		*arg_list;

	file_path = simple_cmd->u_node_data.s_simple_cmd.file_path;
	argv = simple_cmd->u_node_data.s_simple_cmd.args;
	if (argv)
		arg_list = argv->u_node_data.arg_list;
	else
		arg_list = NULL;
	if (ft_strncmp(file_path->u_node_data.file_path_val, "echo", 5) == 0)
		return (ft_echo(app, simple_cmd));
	else if (ft_strncmp(file_path->u_node_data.file_path_val, "export", 7) == 0)
		return (ft_export(app, arg_list));
	else if (ft_strncmp(file_path->u_node_data.file_path_val, "pwd", 4) == 0)
		return (ft_pwd(app, arg_list));
	else if (ft_strncmp(file_path->u_node_data.file_path_val, "cd", 3) == 0)
		return (ft_cd(app, arg_list));
	else if (ft_strncmp(file_path->u_node_data.file_path_val, "env", 4) == 0)
		return (ft_env(app, arg_list));
	else if (ft_strncmp(file_path->u_node_data.file_path_val, "unset", 6) == 0)
		return (ft_unset(app, arg_list));
	else if (ft_strncmp(file_path->u_node_data.file_path_val, "exit", 5) == 0)
		return (ft_exit(app, arg_list));
	return (1);
}
