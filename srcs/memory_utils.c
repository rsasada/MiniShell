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

void	free_env(void *env)
{
	t_env	*e;

	if (env != NULL)
	{
		e = (t_env *) env;
		free(e->key);
		free(e->value);
		free(e);
	}
}
