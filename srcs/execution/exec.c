/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:48:28 by risasada          #+#    #+#             */
/*   Updated: 2024/01/28 00:48:30 by risasada         ###   ########.fr       */
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
		exec_cmd(ast, prev_fd, true);
}

int	execute_cmd(t_ast_node *ast, int *prev_fd, bool last_process)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (last_process)
		return (execute_last_cmd(ast));
	prepare_pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		if (prev_fd[0] != NO_PIPE)
		{
			dup2(prev_fd[0], STDIN_FILENO);
			close(prev_fd[0]);
			close(prev_fd[1]);
		}

	}
	else
	{
		
	}
}

int	execute_last_cmd()
{

}

void	prepare_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}