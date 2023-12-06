/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:29:13 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/11 22:11:32 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static void	*free_str(char **str)
{
	if (!str || !*str)
		return (NULL);
	if (*str)
	{
		free(*str);
		*str = NULL;
		str = NULL;
	}
	return (NULL);
}

static char	*cut_new_line(char *stored_str)
{
	size_t		i;
	size_t		j;
	char		*rest_str;

	i = 0;
	while (stored_str[i] && stored_str[i] != '\n')
		i++;
	if (stored_str[i] == '\0')
		return (free_str(&stored_str));
	rest_str = malloc (sizeof (char) * (ft_strlen (stored_str) + 1));
	if (rest_str == NULL)
		return (free_str(&stored_str));
	i++;
	j = 0;
	while (stored_str[i])
		rest_str[j++] = stored_str[i++];
	rest_str[j] = '\0';
	free (stored_str);
	return (rest_str);
}

static char	*get_new_line(char **stored_str)
{
	size_t		i;
	char		*new_line;

	i = 0;
	if (!*stored_str || (*stored_str)[i] == '\0')
		return (NULL);
	while ((*stored_str)[i] && (*stored_str)[i] != '\n')
		i++;
	if ((*stored_str)[i] != '\n')
		new_line = (char *) malloc (sizeof (char) * (i + 1));
	else
		new_line = (char *) malloc (sizeof (char) * (i + 2));
	if (new_line == NULL)
		return (free_str(stored_str));
	i = 0;
	while ((*stored_str)[i] && (*stored_str)[i] != '\n')
	{
		new_line[i] = (*stored_str)[i];
		i++;
	}
	if ((*stored_str)[i] && (*stored_str)[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

static char	*read_file(int fd, char *buffer, char *stored_str)
{
	ssize_t	r_byte;
	char	*temp;

	r_byte = 1;
	if (stored_str == NULL)
		stored_str = ft_strdup("");
	if (stored_str == NULL)
		return (free_str(&stored_str));
	while ((ft_strchr(stored_str, '\n') == NULL && r_byte != 0))
	{
		r_byte = read(fd, buffer, BUFFER_SIZE);
		if ((r_byte <= 0 && *stored_str == '\0') || r_byte == -1)
			return (free_str(&stored_str));
		buffer[r_byte] = '\0';
		temp = ft_strjoin(stored_str, buffer);
		if (!temp)
			return (free_str(&stored_str));
		free(stored_str);
		stored_str = temp;
		if (stored_str == NULL)
			return (NULL);
	}
	return (stored_str);
}

char	*get_next_line(int fd)
{
	static char		*stored_str = NULL;
	char			*line;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_str (&stored_str));
	stored_str = read_file(fd, buffer, stored_str);
	if (!stored_str || !*stored_str)
		return (free_str (&buffer));
	line = get_new_line (&stored_str);
	if (!line || !stored_str)
		return (free_str (&buffer));
	stored_str = cut_new_line(stored_str);
	free(buffer);
	return (line);
}
