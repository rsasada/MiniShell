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
}
