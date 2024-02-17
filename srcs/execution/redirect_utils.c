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

#include "../../include/minishell.h"


void	add_pid_storage(t_list *pid_storage, pid_t child_pid)
{
	t_list	*new;
	pid_t	*content;

	if (child_pid < 0)
		return ;
	content = malloc(sizeof(pid_t));
	if (content == NULL)
		exit(1);
	*content = child_pid;
	new = ft_lstnew((void *)content);
	ft_lstadd_back(&pid_storage, new);
}

