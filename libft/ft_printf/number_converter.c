/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_converter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:17:24 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:40:14 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	get_base_num(t_specifier *specifier)
{
	if (specifier->fmt_type == 'x' || specifier->fmt_type == 'X')
		return (16);
	else
		return (10);
}

int	get_num_len(long long int num, int base)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		num /= base;
		len++;
	}
	return (len);
}

char	*ft_utoa_base(unsigned int value, char *base)
{
	size_t	buffer_len;
	size_t	base_len;
	char	*str;

	base_len = ft_strlen(base);
	if (value == 0)
		return (ft_strdup("0"));
	buffer_len = get_num_len(value, base_len) + 1;
	str = malloc(sizeof(char) * buffer_len);
	if (!str)
		return (NULL);
	str[--buffer_len] = '\0';
	while (value > 0)
	{
		str[--buffer_len] = base[value % base_len];
		value /= base_len;
	}
	if (buffer_len != 0)
		return (NULL);
	return (str);
}

char	*convert_num(t_specifier *specifier, long long int value)
{
	char	type;

	if (value == 0)
	{
		if (specifier->precision != NO_VALUE)
			return (ft_strdup(""));
		else
			return (ft_strdup("0"));
	}
	type = specifier->fmt_type;
	if (type == 'd' || type == 'i')
	{
		if (value < 0)
			value *= -1;
		return (ft_utoa_base(value, DECIMAL_CHARSET));
	}
	else if (type == 'u')
		return (ft_utoa_base(value, DECIMAL_CHARSET));
	else if (type == 'x' || type == 'p')
		return (ft_utoa_base(value, LHEX_CHARSET));
	else if (type == 'X')
		return (ft_utoa_base(value, UHEX_CHARSET));
	else
		return (NULL);
}
