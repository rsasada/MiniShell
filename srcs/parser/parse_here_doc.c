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

#include "../../include/parser.h"
#include "../../include/lexer.h"

static void	generate_temp_filename(int count, char *filename)
{
	char	*num_str;

	num_str = ft_itoa(count);
	if (num_str == NULL)
		exit_with_error("malloc");
	ft_strlcpy(filename, "/tmp/heredoc_", 14);
	ft_strlcat(filename, num_str, 14 + ft_strlen(num_str));
	ft_strlcat(filename, ".tmp", 19 + ft_strlen(num_str));
	free(num_str);
}

static char	*copy_filename(char *filename)
{
	char	*ret;

	ret = (char *) malloc(sizeof(char) * (ft_strlen(filename) + 1));
	if (!ret)
		exit_with_error("malloc");
	ft_strlcpy(ret, filename, ft_strlen(filename) + 1);
	return (ret);
}

static char	*create_temp_file(void)
{
	char	filename[256];
	int		fd;
	int		count;

	count = 0;
	while (count < HERE_DOC_MAX)
	{
		count++;
		generate_temp_filename(count, filename);
		if (access(filename, F_OK) != -1)
			continue ;
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit_with_error("fd");
		else
		{
			close(fd);
			return (copy_filename(filename));
		}
	}
	return (NULL);
}

static void	write_heredoc_to_file(int fd, char *limiter)
{
	char	*line;

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
}

t_ast_node	*parse_here_doc(t_list **cur_token)
{
	char	*limiter;
	char	*filename;
	int		fd;

	limiter = ((t_token *)(*cur_token)->content)->value;
	filename = create_temp_file();
	if (!filename)
		return (NULL);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_with_error("here_doc");
	write_heredoc_to_file(fd, limiter);
	close(fd);
	return (create_file_name_node(filename));
}
