/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:48:28 by risasada          #+#    #+#             */
/*   Updated: 2024/02/02 18:35:36 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	execute_execve(t_ast_node *simple_cmd, t_app *app);
void	execute_last_cmd(t_ast_node *cmd, int *prev_fd, t_app *app);
void	execute_cmd(t_ast_node *ast, int *prev_fd,
			bool last_process, t_app *app);
void	process_cmds(t_ast_node *ast, int *prev_fd, t_app *app);
char	**get_args(t_ast_node *simple_cmd);

void	execute(t_ast_node *ast, t_app *app)
{
	int	prev_fd[2];

	prev_fd[0] = NO_PIPE;
	prev_fd[1] = NO_PIPE;
	if (ast == NULL)
		return ;
	process_cmds(ast, prev_fd, app);
}

void	process_cmds(t_ast_node *ast, int *prev_fd, t_app *app)
{
	if (ast->node_type == NODE_PIPELINE)
	{
		if (ast->u_node_data.s_pipeline.right->node_type == NODE_PIPELINE)
		{
			execute_cmd(ast->u_node_data.s_pipeline.left, prev_fd, false, app);
			process_cmds(ast->u_node_data.s_pipeline.right, prev_fd, app);
		}
		else
		{
			execute_cmd(ast->u_node_data.s_pipeline.left, prev_fd, false, app);
			execute_cmd(ast->u_node_data.s_pipeline.right, prev_fd, true, app);
		}
	}
	else if (ast->node_type == NODE_CMD && prev_fd[0] == NO_PIPE)
		execute_cmd(ast, prev_fd, true, app);
}

void	execute_cmd(t_ast_node *ast, int *prev_fd,
				bool last_process, t_app *app)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (last_process)
		return (execute_last_cmd(ast, prev_fd, app));
	prepare_pipe(pipe_fd);
	pid = safe_fork();
	if (pid == 0)
	{
		if (prev_fd[0] != NO_PIPE)
			redirect_input_to_pipe(prev_fd);
		redirect_output_to_pipe(pipe_fd);
		process_redirects(ast->u_node_data.s_cmd.redirection, NULL);
		execute_execve(ast->u_node_data.s_cmd.simple_cmd, app);
		exit(0);
	}
	else
	{
		if (prev_fd[0] != NO_PIPE)
			close_pipe(prev_fd);
		prev_fd[0] = pipe_fd[0];
		prev_fd[1] = pipe_fd[1];
		add_pid_storage(app, pid);
		return ;
	}
}

void	execute_last_cmd(t_ast_node	*cmd, int *prev_fd, t_app *app)
{
	pid_t		pid;

	if (prev_fd[0] == NO_PIPE && check_builtin_cmd(
			cmd->u_node_data.s_cmd.simple_cmd))
	{
		execute_single_builtin_cmd(cmd, app);
		return ;
	}
	pid = safe_fork();
	if (pid == 0)
	{
		if (prev_fd[0] != NO_PIPE)
			redirect_input_to_pipe(prev_fd);
		process_redirects(cmd->u_node_data.s_cmd.redirection, NULL);
		execute_execve(cmd->u_node_data.s_cmd.simple_cmd, app);
		exit(0);
	}
	else
	{
		if (prev_fd[0] != NO_PIPE)
			close_pipe(prev_fd);
		wait_child(pid, app->pid_storage);
	}
}

void	execute_execve(t_ast_node *simple_cmd, t_app *app)
{
	char	**env_path;
	char	*cmd_path;
	char	**args;

	config_signal(CHILD);
	if (simple_cmd == NULL)
		return ;
	if (check_builtin_cmd(simple_cmd))
		exit(builtin_functions(simple_cmd, app));
	args = get_args(simple_cmd);
	env_path = convert_env_to_char(app->env_lst);
	cmd_path = get_cmd_path(simple_cmd->u_node_data.s_simple_cmd.file_path,
			split_env_path(app->env_lst));
	validate_cmd_path(cmd_path, simple_cmd->u_node_data.s_simple_cmd.file_path);
	if (execve(cmd_path, args, env_path) == -1)
		exit(errno);
}
