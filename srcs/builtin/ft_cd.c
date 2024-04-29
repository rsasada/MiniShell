/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:29:24 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/18 17:29:24 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static void	update_pwd(t_app *app, char *cwd)
{
	char	*pwd;
	char	*oldpwd;

	if (!cwd)
	{
		perror("cd: error retrieving current directory: " \
		"getcwd: cannot access parent directories");
		pwd = ft_strjoin(app->cur_directory, "/.");
	}
	else
		pwd = cwd;
	oldpwd = ft_strdup(((t_env *) \
			(find_env(&app->env_lst, "PWD")->content))->value);
	if (!oldpwd)
		exit_with_error("Malloc");
	add_env(&app->env_lst, "PWD", pwd);
	free(app->cur_directory);
	app->cur_directory = ft_strdup(pwd);
	add_env(&app->env_lst, "OLDPWD", oldpwd);
	free(oldpwd);
	free(pwd);
}

static int	chdir_oldpwd(t_list *env_list)
{
	char	*oldpwd_path;

	oldpwd_path = ((t_env *) \
	(find_env(&env_list, "OLDPWD")->content))->value;
	if (oldpwd_path == NULL)
	{
		ft_putendl_fd("push: cd: OLDPWD not set", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static int	chdir_home(t_app *app, t_list *env_list, int argc)
{
	t_list	*home_env;
	char	*home_path;

	home_env = (find_env(&env_list, "HOME"));
	if (home_env)
		home_path = ((t_env *)home_env->content)->value;
	else
		home_path = NULL;
	if (!home_path && !app->home_path)
		exit_with_error("Unexpected : No Home path set");
	if (!home_path && argc == 0)
	{
		ft_putendl_fd("push: cd: HOME not set", STDERR_FILENO);
		return (false);
	}
	else if (!home_path)
		return (ft_chdir(app->home_path));
	else
		return (ft_chdir(home_path));
}

static void	chdir_home_with_path(t_app *app, char *path)
{
	char	*home_path;
	char	*full_path;

	home_path = app->home_path;
	if (!home_path && !app->home_path)
		exit_with_error("Unexpected : No Home path set");
	full_path = ft_strjoin(home_path, (path + 1));
	if (!full_path)
		exit_with_error("malloc");
	ft_chdir(full_path);
	free(full_path);
}

int	ft_cd(t_app *app, t_list *argv)
{
	char	*path;
	char	*cwd;
	t_list	*env_list;
	int		status;

	status = 0;
	env_list = app->env_lst;
	if (!argv)
		chdir_home(app, env_list, 0);
	else
	{
		path = ((t_ast_node *)(argv->content))->u_node_data.file_name_val;
		if (ft_strncmp(path, "~", 2) == 0)
			status = chdir_home(app, env_list, 1);
		else if (ft_strncmp(path, "~/", 2) == 0)
			chdir_home_with_path(app, path);
		else if (ft_strncmp(path, "-", 2) == 0)
			status = chdir_oldpwd(env_list);
		else
			status = ft_chdir(path);
	}
	if (!status)
		return (BUILTIN_FAILURE);
	cwd = getcwd(NULL, 0);
	update_pwd(app, cwd);
	return (BUILTIN_SUCCESS);
}
