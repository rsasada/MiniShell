/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:08:58 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:42:01 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	print_specifier(t_specifier *specifier, va_list ap)
{
	if (specifier->fmt_type == PLAIN_FORMAT)
		return (print_plain_text(specifier));
	if (specifier->fmt_type == 'c')
		return (print_char(specifier, va_arg (ap, int)));
	else if (specifier->fmt_type == 's')
		return (print_str(specifier, va_arg (ap, char *)));
	else if (specifier->fmt_type == 'p')
		return (print_ptr(specifier, va_arg (ap, void *)));
	else if (specifier->fmt_type == 'd' || specifier->fmt_type == 'i')
		return (print_num(specifier, va_arg (ap, int)));
	else if (specifier->fmt_type == 'u')
		return (print_num(specifier, va_arg (ap, unsigned int)));
	else if (specifier->fmt_type == 'x')
		return (print_num(specifier, va_arg (ap, unsigned int)));
	else if (specifier->fmt_type == 'X')
		return (print_num(specifier, va_arg (ap, unsigned int)));
	else if (specifier->fmt_type == '%')
		return (print_char(specifier, PERCENT_SYMBOL));
	else
		return (OPERATION_ERROR);
}

int	print_format(t_list *lst, va_list ap)
{
	t_specifier	*specifier;
	int			tmp;
	int			ret;

	ret = 0;
	while (lst != NULL)
	{
		specifier = lst->content;
		tmp = print_specifier(specifier, ap);
		if (tmp < 0)
			return (tmp);
		ret += tmp;
		lst = lst->next;
	}
	return (ret);
}
