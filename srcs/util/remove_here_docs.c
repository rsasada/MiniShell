/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_here_docs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:14:21 by jongykim          #+#    #+#             */
/*   Updated: 2024/03/20 22:14:21 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	remove_file(char *file_name, int num_length)
{
	char	*absolute_path;

	if (ft_atoi(file_name + 8) >= 0 && ft_atoi(file_name + 8) <= HERE_DOC_MAX \
	&& ft_strncmp(".tmp", (file_name + 8 + num_length), 5) == 0)
	{
		absolute_path = ft_strjoin("/tmp/", file_name);
		unlink(absolute_path);
		free(absolute_path);
	}
}

static struct dirent	*get_file_list(DIR *temp_dir)
{
	if (!temp_dir)
		exit_with_error("opendir");
	return (readdir(temp_dir));
}

void	clear_tmp(void)
{
	DIR				*temp_dir;
	struct dirent	*file_list;
	char			*file_name;
	int				i;

	temp_dir = opendir("/tmp");
	file_list = get_file_list(temp_dir);
	while (file_list != NULL)
	{
		if (file_list->d_type == DT_REG)
		{
			file_name = file_list->d_name;
			if (ft_strncmp("heredoc_", file_name, 8) == 0)
			{
				i = 0;
				while (ft_isdigit(file_name[8 + i]))
					i++;
				remove_file(file_name, i);
			}
		}
		file_list = readdir(temp_dir);
	}
	closedir(temp_dir);
}
