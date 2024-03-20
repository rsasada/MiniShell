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

#include "../../include/execution.h"

void	redirect(t_ast_node *s_r, int *flag);
void	redirect_input(t_ast_node *s_r, int *flag);
void	redirect_output(t_ast_node *s_r, int *flag);
void	redirect_append(t_ast_node *s_r, int *flag);

void	process_redirects(t_ast_node *s_r, int *flag)
{
	if (s_r == NULL)
		return ;
	if (s_r->node_type == NODE_PIPELINE)
	{
		if (s_r->u_node_data.s_pipeline.right->node_type == NODE_PIPELINE)
		{
			process_redirects(s_r->u_node_data.s_pipeline.left, flag);
			process_redirects(s_r->u_node_data.s_pipeline.right, flag);
		}
		else
		{
			process_redirects(s_r->u_node_data.s_pipeline.left, flag);
			process_redirects(s_r->u_node_data.s_pipeline.right, flag);
		}
	}
	else if (s_r->node_type == NODE_REDIRECTION)
		redirect(s_r, flag);
}

void	redirect(t_ast_node *s_r, int *flag)
{
	if (s_r == NULL || s_r->node_type != NODE_REDIRECTION)
		return ;
	if (ft_strncmp(s_r->u_node_data.s_redirection.op, ">", 2) == 0)
		redirect_output(s_r, flag);
	else if (ft_strncmp(s_r->u_node_data.s_redirection.op, "<", 2) == 0
		|| ft_strncmp(s_r->u_node_data.s_redirection.op, "<<", 3) == 0)
		redirect_input(s_r, flag);
	else if (ft_strncmp(s_r->u_node_data.s_redirection.op, ">>", 3) == 0)
		redirect_append(s_r, flag);
}

void	redirect_input(t_ast_node *s_r, int *flag)
{
	int			file_fd;
	t_ast_node	*file_name;

	if (flag == NULL)
		file_fd = 0;
	else if (*flag == 1)
		return ;
	file_name = s_r->u_node_data.s_redirection.file_name;
	file_fd = open(file_name->u_node_data.file_name_val,
			O_RDONLY, 0644);
	if (file_fd < 0)
	{
		ft_putstr_fd("push: ", 2);
		perror(file_name->u_node_data.file_name_val);
		if (flag == NULL)
			exit(1);
		*flag = 1;
	}
	dup2(file_fd, 0);
	close(file_fd);
}

void	redirect_output(t_ast_node *s_r, int *flag)
{
	int			file_fd;
	t_ast_node	*file_name;

	if (flag == NULL)
		file_fd = 0;
	else if (*flag == 1)
		return ;
	file_name = s_r->u_node_data.s_redirection.file_name;
	file_fd = open(file_name->u_node_data.file_name_val,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_fd < 0)
	{
		ft_putstr_fd("push: ", 2);
		perror(file_name->u_node_data.file_name_val);
		if (flag == NULL)
			exit(1);
		*flag = 1;
	}
	dup2(file_fd, 1);
	close(file_fd);
}

void	redirect_append(t_ast_node *s_r, int *flag)
{
	int			file_fd;
	t_ast_node	*file_name;

	if (flag == NULL)
		file_fd = 0;
	else if (*flag == 1)
		return ;
	file_name = s_r->u_node_data.s_redirection.file_name;
	file_fd = open(file_name->u_node_data.file_name_val,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file_fd < 0)
	{
		ft_putstr_fd("push: ", 2);
		perror(file_name->u_node_data.file_name_val);
		if (flag == NULL)
			exit(1);
		*flag = 1;
	}
	dup2(file_fd, 1);
	close(file_fd);
}
