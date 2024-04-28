/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:32:46 by jongykim          #+#    #+#             */
/*   Updated: 2024/04/26 20:32:46 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*handling_missing_home(void)
{
	char	*cur_directory;
	int		i;
	int		j;
	char	*ret;

	ret = NULL;
	i = 0;
	j = 0;
	cur_directory = getcwd(NULL, 0);
	if (!cur_directory)
		exit_with_error("getcwd");
	while (cur_directory[i] && j < 2)
	{
		while (cur_directory[i] && cur_directory[i] == '/')
			i++;
		while (cur_directory[i] && cur_directory[i] != '/')
			i++;
		j++;
	}
	ret = ft_substr(cur_directory, 0, i);
	if (!ret)
		exit_with_error("malloc");
	free(cur_directory);
	return (ret);
}

char	*get_home(t_app *app)
{
	char	*ret;

	ret = NULL;
	if (getenv("HOME") == NULL)
		return (handling_missing_home());
	ret = ft_strdup(\
		((t_env *) find_env(&app->env_lst, "HOME")->content)->value);
	if (!ret)
		exit_with_error("malloc");
	return (ret);
}
