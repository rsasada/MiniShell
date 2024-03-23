/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:20:50 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/12 14:20:50 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_env(t_app *app, t_list *arg)
{
	t_list	*env_list;
	t_list	*cur;

	if (arg)
	{
		g_signal = 1;
		ft_putendl_fd("push: too many arguments", 2);
		return (0);
	}
	env_list = app->env_lst;
	cur = env_list;
	while (cur)
	{
		printf("%s", ((t_env *)(cur->content))->key);
		printf("=");
		printf("%s", ((t_env *)(cur->content))->value);
		printf("\n");
		cur = cur->next;
	}
	g_signal = 0;
	return (1);
}
