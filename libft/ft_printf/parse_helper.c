/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:08:08 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:40:18 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	read_nbr(char **fmt)
{
	char	*tmp;
	int		number;

	tmp = *fmt;
	while (ft_isdigit(**fmt))
		(*fmt)++;
	if (tmp != *fmt)
		number = ft_atoi(tmp);
	else
		number = 0;
	return (number);
}

int	read_flags(t_specifier *specifier, char **fmt)
{
	if (!fmt || !*fmt)
		return (OPERATION_ERROR);
	(*fmt)++;
	while ((**fmt == '#' || **fmt == ' ' || **fmt == '+'
			|| **fmt == '-' || **fmt == '0'))
	{
		if (**fmt == '#')
			specifier->alternate_form = TRUE;
		else if (**fmt == '0')
			specifier->zero_padding = TRUE;
		else if (**fmt == '-')
			specifier->left_justify = TRUE;
		else if (**fmt == ' ')
			specifier->blank_space = TRUE;
		else if (**fmt == '+')
		{
			specifier->sign_specified = TRUE;
		}
		(*fmt)++;
	}
	return (OPERATION_SUCCESS);
}

void	read_minwidth(t_specifier *specifier, char **fmt)
{
	specifier->width = read_nbr(fmt);
	if (specifier->width < 0)
		specifier->width = NO_VALUE;
}

void	read_precision(t_specifier *specifier, char **fmt)
{
	if (**fmt == '.')
	{
		(*fmt)++;
		specifier->precision = read_nbr(fmt);
		if (specifier->precision <= -1)
			specifier->precision = NO_VALUE;
	}
}

int	read_types(t_specifier *specifier, char **fmt)
{
	char	*types_char;
	char	*p;

	types_char = "cspdiuxX%";
	p = ft_strchr(types_char, **fmt);
	if (p)
	{
		(*fmt)++;
		specifier->fmt_type = *p;
		return (OPERATION_SUCCESS);
	}
	return (OPERATION_ERROR);
}
