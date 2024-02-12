/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:51:48 by risasada          #+#    #+#             */
/*   Updated: 2024/02/02 20:51:50 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"
#include "../../include/parser.h"

<<<<<<< HEAD
void	redirect(t_ast_node *s_r);
void	redirect_input(t_ast_node *s_r);
void	redirect_output(t_ast_node *s_r);
void	redirect_append(t_ast_node *s_r);

void	process_redirects(t_ast_node *s_r)
{
	if (s_r->node_type == NODE_PIPELINE)
	{
		if (s_r->u_node_data.s_pipeline.right->node_type == NODE_PIPELINE)
		{
			process_redirects(s_r->u_node_data.s_pipeline.left);
			process_redirects(s_r->u_node_data.s_pipeline.right);
		}
		else
		{
			process_redirects(s_r->u_node_data.s_pipeline.left);
			process_redirects(s_r->u_node_data.s_pipeline.right);
		}
	}
	else if (s_r->node_type == NODE_REDIRECTION)
		redirect(s_r);
}

void	redirect(t_ast_node *s_r)
{
	int			file_fd;
	t_ast_node	*file_name;

	if (s_r == NULL || s_r->node_type != NODE_REDIRECTION)
		return ;
	if (ft_strncmp(s_r->u_node_data.s_redirection.op, ">", 2) == 0)
		redirect_output(s_r);
	else if (ft_strncmp(s_r->u_node_data.s_redirection.op, "<", 2) == 0
		|| ft_strncmp(s_r->u_node_data.s_redirection.op, "<<", 3) == 0)
		redirect_input(s_r);
	else if (ft_strncmp(s_r->u_node_data.s_redirection.op, ">>", 3) == 0)
		redirect_append(s_r);
}

void	redirect_input(t_ast_node *s_r)
{
	int			file_fd;
	t_ast_node	*file_name;

	file_name = s_r->u_node_data.s_redirection.file_name;
	file_fd = open(file_name->u_node_data.file_name_val,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(file_fd, 0);
	close(file_fd);
}

void	redirect_output(t_ast_node *s_r)
{
	int			file_fd;
	t_ast_node	*file_name;

	file_name = s_r->u_node_data.s_redirection.file_name;
	file_fd = open(file_name->u_node_data.file_name_val,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(file_fd, 1);
	close(file_fd);
}

void	redirect_append(t_ast_node *s_r)
{
	int			file_fd;
	t_ast_node	*file_name;

	file_name = s_r->u_node_data.s_redirection.file_name;
	file_fd = open(file_name->u_node_data.file_name_val,
			O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0644);
	dup2(file_fd, 1);
	close(file_fd);
=======
void	execute_redirect(t_ast_node *s_r)
{
	int	prev_fd;

	if (s_r == NULL)
		return ;
	prev_fd = 1;
	process_redirect(s_r, &prev_fd);
}

void	process_redirect(t_ast_node *s_r, int *prev_fd)
{
	if (s_r->node_type == NODE_PIPELINE)
	{
		redirect(s_r, prev_fd);
		process_redirect(s_r->u_node_data.s_pipeline.right, prev_fd);
	}
	else if (s_r->node_type == NODE_REDIRECTION)
	{
		redirect(s_r, prev_fd);
		redirect(s_r, prev_fd);
	}
	else if (s_r->node_type == NODE_REDIRECTION && *prev_fd == 1)
	{
	}
>>>>>>> 5e14497a4aeaa3072d7b5ae226773715b93dabef
}
