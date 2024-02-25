/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 03:35:07 by jongykim          #+#    #+#             */
/*   Updated: 2024/01/28 03:35:07 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *) content;
	if (token != NULL)
	{
		free(token->value);
		free(token);
	}
}
