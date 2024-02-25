/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:52:09 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/25 20:52:09 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_temp_file(void)
{
	char	filename[256];
	char	*num_str;
	int		fd;
	int		count;
	char	*ret;

	count = 0;
	while (count < HERE_DOC_MAX)
	{
		count++;
		num_str = ft_itoa(count);
		if (num_str == NULL)
			continue ;
		ft_strlcpy(filename, "/tmp/here_doc_", 15);
		ft_strlcat(filename, num_str, 15 + ft_strlen(num_str));
		ft_strlcat(filename, ".tmp", 21 + ft_strlen(num_str));
		free(num_str);
		if (access(filename, F_OK) != -1)
			continue ;
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			continue ;
		else
		{
			close(fd);
			ret = (char *) malloc(sizeof(char) * (ft_strlen(filename) + 1));
			if (!ret)
				return (NULL);
			ft_strlcpy(ret, filename, ft_strlen(filename) + 1);
			return (ret);
		}
	}
	return (NULL);
}

t_ast_node	*parse_here_doc(t_list **cur_token)
{
	char	*limiter;
	char	*line;
	char	*filename;
	int		fd;

	limiter = ((t_token *)(*cur_token)->content)->value;
	filename = create_temp_file();
	if (!filename)
		return (NULL);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_with_error("here_doc");
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (create_file_name_node(filename));
}
