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

#include "../../include/minishell.h"
#include "../../include/execution.h"
#include "../../include/parser.h"

void	execute_execve(t_ast_node *simple_cmd, t_app *app);
void	execute_last_cmd(t_ast_node *ast, int *prev_fd);
void	execute_cmd(t_ast_node *ast, int *prev_fd, bool last_process);
void	process_cmds(t_ast_node *ast, int *prev_fd);

void	execute(t_ast_node *ast, t_app *app)
{
	int	prev_fd[2];

	prev_fd[0] = NO_PIPE;
	prev_fd[1] = NO_PIPE;
	if (ast == NULL)
		return ;
	process_cmds(ast, prev_fd);
}

void	process_cmds(t_ast_node *ast, int *prev_fd)
{
	if (ast->node_type == NODE_PIPELINE)
	{
		if (ast->u_node_data.s_pipeline.right->node_type == NODE_PIPELINE)
		{
			execute_cmd(ast->u_node_data.s_pipeline.left, prev_fd, false);
			process_cmds(ast->u_node_data.s_pipeline.right, prev_fd);
		}
		else
		{
			execute_cmd(ast->u_node_data.s_pipeline.left, prev_fd, false);
			execute_cmd(ast->u_node_data.s_pipeline.right, prev_fd, true);
		}
	}
	else if (ast->node_type == NODE_CMD && prev_fd[0] == NO_PIPE)
		execute_cmd(ast, prev_fd, true);
}

void	execute_cmd(t_ast_node *ast, int *prev_fd, bool last_process)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (last_process)
		return (execute_last_cmd(ast, prev_fd));
	prepare_pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		if (prev_fd[0] != NO_PIPE)
			redirect_input_to_pipe(prev_fd);
		redirect_output_to_pipe(pipe_fd);
		process_redirects(ast->u_node_data.s_cmd.redirection);
		execute_execuve(ast->u_node_data.s_cmd.simple_cmd);
		exit(0);
	}
	else
	{
		if (prev_fd[0] != NO_PIPE)
			close_pipe(prev_fd);
		prev_fd[0] = pipe_fd[0];
		prev_fd[1] = pipe_fd[1];
		return ;
	}
}

void	execute_last_cmd(t_ast_node *ast, int *prev_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (prev_fd[0] != NO_PIPE)
			redirect_input_to_pipe(prev_fd);
		process_redirects(ast->u_node_data.s_cmd.redirection);
		write(1, "test", 5);
		exit(0);
	}
	else
	{
		if (prev_fd[0] != NO_PIPE)
			close_pipe(prev_fd);
		wait(&pid);
	}
}

void	execute_execve(t_ast_node *simple_cmd, t_app *app)
{
	char	**env_path;
	char	*cmd_path;
	char	**args;

	args = 
	env_path = split_env_path(app);
	cmd_path = check_access(simple_cmd->u_node_data.s_simple_cmd.file_path,
			env_path);
	if (cmd_path == NULL)
		//error_massage
	execve()
}
