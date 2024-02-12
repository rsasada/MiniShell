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

void	execute(t_ast_node *ast)
{
	int	prev_fd[2];

	prev_fd[0] = NO_PIPE;
	prev_fd[1] = NO_PIPE;
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

int	execute_cmd(t_ast_node *ast, int *prev_fd, bool last_process)
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
		execute_redirect();
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

int	execute_last_cmd(t_ast_node *ast, int *prev_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (prev_fd[0] != NO_PIPE)
			redirect_input_to_pipe(prev_fd);
		execute_redirect(ast->u_node_data.s_cmd.redirection);
	}
	else
	{
		if (prev_fd[0] != NO_PIPE)
			close_pipe(prev_fd);
		
	}
}

void	prepare_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}
