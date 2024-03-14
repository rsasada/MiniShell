/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   examine_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:42:33 by jongykim          #+#    #+#             */
/*   Updated: 2024/03/13 02:42:33 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	is_path_exist(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (1);
	else
		return (0);
}

char	*get_full_path(char *cmd, char *env_path)
{
	char	*temp;
	char	*ret;

	temp = ft_strjoin(env_path, "/");
	ret = ft_strjoin(temp, cmd);
	free(temp);
	return (ret);
}

void	validate_cmd_path(char *cmd_path, t_ast_node *cmd_node)
{
	char		*cmd;
	struct stat	buf;

	cmd = cmd_node->u_node_data.file_path_val;
	if (cmd_path == 0)
		custom_error(127, CMD_NOT_FOUND, cmd);
	else if (access(cmd_path, X_OK) == -1)
		custom_error(126, PERM_DENIED, cmd);
	stat(cmd_path, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		custom_error(126, IS_DIR, cmd);
}

char	*get_cmd_path(t_ast_node *file_node, char **env_path)
{
	char	*cmd;
	char	*full_path;
	int		i;

	cmd = file_node->u_node_data.file_path_val;
	if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0)
	{
		if (is_path_exist(cmd))
			return (cmd);
		custom_error(127, FILE_NOT_FOUND, cmd);
	}
	i = 0;
	if (!env_path)
		custom_error(127, FILE_NOT_FOUND, cmd);
	while (env_path && env_path[i])
	{
		full_path = get_full_path(cmd, env_path[i]);
		if (is_path_exist(full_path))
			return (full_path);
		i++;
	}
	return (NULL);
}
