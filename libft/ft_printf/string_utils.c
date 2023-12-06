/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 01:24:48 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:42:07 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	print_plain_text(t_specifier *specifier)
{
	char	*s;
	char	*e;

	s = specifier->start;
	e = specifier->end;
	return (write(STDOUT_FILENO, s, e - s));
}

int	append_str(char **des, char *src)
{
	char	*buf;

	if (!src)
		return (OPERATION_ERROR);
	buf = ft_strjoin(*des, src);
	free(*des);
	if (!buf)
		return (OPERATION_ERROR);
	*des = buf;
	return (OPERATION_SUCCESS);
}

int	append_padding(t_specifier *specifier, char **buf)
{
	int		ret;
	char	*padding;
	char	*temp;

	padding = get_padding(specifier, ft_strlen(*buf));
	if (!padding)
		return (OPERATION_ERROR);
	if (specifier->left_justify == FALSE)
	{
		temp = *buf;
		*buf = padding;
		padding = temp;
	}
	ret = append_str(buf, padding);
	free(padding);
	if (ret < 0)
		return (OPERATION_ERROR);
	return (OPERATION_SUCCESS);
}
