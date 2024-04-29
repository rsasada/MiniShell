/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:07:11 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/24 16:07:11 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_chdir(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("push: cd: ", STDERR_FILENO);
		perror(path);
		return (BUILTIN_FAILURE);
	}
	return (BUILTIN_SUCCESS);
}

void	print_env(t_app *app, int is_export)
{
	t_list	*env_list;
	t_list	*cur;

	env_list = app->env_lst;
	cur = env_list;
	while (cur)
	{
		if (is_export)
			printf("declare -x ");
		printf("%s", ((t_env *)(cur->content))->key);
		printf("=");
		if (is_export)
			printf("\"");
		printf("%s", ((t_env *)(cur->content))->value);
		if (is_export)
			printf("\"");
		printf("\n");
		cur = cur->next;
	}
}
