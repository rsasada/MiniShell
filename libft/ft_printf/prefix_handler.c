/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:17:50 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:40:35 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*apply_sign(t_specifier *specifier, long long int num)
{
	if (num >= 0)
	{
		if (specifier->fmt_type != 'd' && specifier -> fmt_type != 'i')
			return (ft_strdup(""));
		if (specifier->sign_specified)
			return (ft_strdup(POSITIVE_SIGN));
		else if (specifier->blank_space)
			return (ft_strdup(BLANK_PREFIX));
		return (ft_strdup(""));
	}
	else
		return (ft_strdup(NEGATIVE_SIGN));
}

int	apply_hex_prefix(t_specifier *specifier, size_t num, char **buf)
{
	int	base;

	base = get_base_num(specifier);
	if (base == 16 && specifier->alternate_form && num != 0)
	{
		if (specifier->fmt_type == 'x' && append_str(buf, LHEX_PREFIX) < 0)
			return (OPERATION_ERROR);
		if (specifier->fmt_type == 'X' && append_str(buf, UHEX_PREFIX) < 0)
			return (OPERATION_ERROR);
	}
	return (OPERATION_SUCCESS);
}

int	apply_precision(t_specifier *specifier, size_t num, char **buf)
{
	int		num_len;
	char	*temp;
	int		padding_len;
	int		result;

	num_len = get_num_len(num, get_base_num(specifier));
	if (specifier->precision != NO_VALUE && specifier->precision > num_len)
	{
		padding_len = specifier->precision - num_len;
		temp = append_pad_for_prefix(padding_len, ZEROPAD_SYMBOL);
		if (!temp)
			return (OPERATION_ERROR);
		result = append_str(buf, temp);
		free(temp);
		if (result < 0)
			return (OPERATION_ERROR);
	}
	return (OPERATION_SUCCESS);
}

char	*append_pad_for_prefix(int padding_len, char symbol)
{
	char	*padding;

	padding = (char *) malloc(sizeof(char) * (padding_len + 1));
	if (!padding)
		return (NULL);
	ft_memset(padding, symbol, padding_len);
	padding[padding_len] = '\0';
	return (padding);
}
