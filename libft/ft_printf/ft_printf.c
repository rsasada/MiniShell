/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:07:50 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:40:06 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	int			ret;
	t_list		*format_specifiers;

	format_specifiers = NULL;
	if (parse_formats(&format_specifiers, format) < 0)
	{
		ft_lstclear (&format_specifiers, free);
		return (OPERATION_ERROR);
	}
	va_start(ap, format);
	ret = print_format(format_specifiers, ap);
	va_end(ap);
	ft_lstclear (&format_specifiers, free);
	return (ret);
}
