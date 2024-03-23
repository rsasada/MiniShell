/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:38:54 by risasada          #+#    #+#             */
/*   Updated: 2024/02/08 21:38:56 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	add_pid_storage(t_app *app, pid_t child_pid)
{
	t_list	*new;
	pid_t	*content;

	if (child_pid < 0)
		return ;
	if (app == NULL)
		return ;
	content = malloc(sizeof(pid_t));
	if (content == NULL)
		exit(1);
	*content = child_pid;
	new = ft_lstnew((void *)content);
	ft_lstadd_back(&app->pid_storage, new);
}
