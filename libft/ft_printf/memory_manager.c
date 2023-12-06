/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:07:50 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:40:10 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	free_strs(int count, ...)
{
	va_list	ap;
	char	**s;
	int		i;

	va_start(ap, count);
	i = 0;
	while (i++ < count)
	{
		s = va_arg(ap, char **);
		if (*s)
			free(*s);
		*s = NULL;
	}
	va_end(ap);
}

void	*free_str(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

int	free_buf_with_error(char **buf)
{
	if (*buf != NULL)
	{
		free(*buf);
		*buf = NULL;
	}
	return (OPERATION_ERROR);
}
