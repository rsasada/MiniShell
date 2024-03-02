
#include "../../include/execution.h"

bool	execute_single_builtin_cmd(t_ast_node *ast, t_app *app)
{
	int			stdin_backup;
	int			stdout_backup;
	t_ast_node	*simple_cmd;
	t_ast_node	*redirection;

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

bool	check_builtin_cmd(char *cmd_name)
{
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

bool	builtin_functions(t_ast_node *simple_cmd, t_app *app)
{
	char	*file_path;

	file_path = simple_cmd->u_node_data.s_simple_cmd.file_path;
	if (ft_strncmp(file_path, "echo", 5) == 0)
		return (ft_echo(simple_cmd, app));
	else if (ft_strncmp(file_path, "export", 7) == 0)
		return (ft_export(simple_cmd, app));
	else if (ft_strncmp(file_path, "pwd", 4) == 0)
		return (ft_pwd(simple_cmd, app));
	else if (ft_strncmp(file_path, "cd", 3) == 0)
		return (ft_cd(simple_cmd, app));
	else if (ft_strncmp(file_path, "env", 4) == 0)
		return (ft_env(simple_cmd, app));
	else if (ft_strncmp(file_path, "unset", 6) == 0)
		return (ft_unset(simple_cmd, app));
	else if (ft_strncmp(file_path, "exit", 5) == 0)
		return (ft_exit(simple_cmd, app));
	return (false);
}