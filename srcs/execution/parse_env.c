/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:57:41 by risasada          #+#    #+#             */
/*   Updated: 2024/02/12 17:57:43 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"


int		wrapped_access(char *path, int *error_code);
void	exit_access_error(int error_code, char *path);

char	*check_access(t_ast_node *file_path, char **env_path)
{
	int		i;
	int		error_code;
	char	*path;
	char	*tmp;
	char	*absol_path;

	i = 0;
	error_code = 0;
	path = file_path->u_node_data.file_path_val;
	if (wrapped_access(path, &error_code) == 0)
		return (path);
	while (env_path[i] != NULL)
	{
		tmp = ft_strjoin(env_path[i], "/");
		absol_path = ft_strjoin(tmp, path);
		free(tmp);
		if (wrapped_access(absol_path, &error_code) == 0)
			return (absol_path);
		free(absol_path);
		i ++;
	}
	exit_access_error(error_code, path);
	return (NULL);
}

int	wrapped_access(char *path, int *error_code)
{
	if (path == NULL)
		return (1);
	if (access(path, F_OK) != 0 && *error_code != X_OK)
	{
		*error_code = F_OK;
		return (1);
	}
	if (access(path, X_OK) != 0)
	{
		*error_code = X_OK;
		return (1);
	}
	return (0);
}

void	exit_access_error(int error_code, char *path)
{
	if (error_code == F_OK)
	{
		ft_putstr_fd("push: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": command not found ", STDERR_FILENO);
	}
	else if (error_code == X_OK)
	{
		ft_putstr_fd("push: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": Pemission denied ", STDERR_FILENO);
	}
}

char	**split_env_path(t_list *env_list)
{
	char	*path;
	t_env	*env;

	while (env_list != NULL)
	{
		env = env_list->content;
		if (ft_strncmp(env->key, "PATH", 5) == 0)
		{
			path = env->value;
			return (ft_split(path, ':'));
		}
		env_list = env_list->next;
	}
	return (NULL);
}

char	**convert_env_to_char(t_list *env_list)
{
	char	**env_array;
	char	*tmp;
	t_env	*env;
	int		list_size;
	int		i;

	i = 0;
	list_size = ft_lstsize(env_list);
	if (list_size == 0)
		return (NULL);
	env_array = (char **)malloc(sizeof(char *) * (list_size + 1));
	if (env_array == NULL)
		exit(1);
	while (env_list != NULL)
	{
		env = env_list->content;
		tmp = ft_strjoin(env->key, "=");
		env_array[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		i ++;
		env_list = env_list->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
