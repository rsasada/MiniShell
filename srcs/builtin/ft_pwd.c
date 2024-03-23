/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:24:23 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/23 00:24:23 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_pwd(t_app *app, t_list *argv)
{
	char	*cwd;

	(void)app;
	(void)argv;
	cwd = getcwd(NULL, 0);
	if (cwd)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else if (app->cur_directory)
		ft_putendl_fd(app->cur_directory, STDOUT_FILENO);
	else
		exit_with_error("unexpected : failed getcwd ");
	free(cwd);
	return (0);
}
