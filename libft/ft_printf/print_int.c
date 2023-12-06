/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:06:30 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:40:53 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*get_prefix(t_specifier *specifier, size_t num)
{
	char	*buf;

	buf = apply_sign(specifier, num);
	if (!buf)
		return (NULL);
	if (apply_hex_prefix(specifier, num, &buf) < 0)
		return (free_str(&buf));
	if (apply_precision(specifier, num, &buf) < 0)
		return (free_str(&buf));
	return (buf);
}

char	*get_padding(t_specifier *specifier, int filled)
{
	int		padding_len;
	char	padding_char;
	char	*padding;

	padding_len = 0;
	if (specifier->width != NO_VALUE && specifier->width > filled)
		padding_len = specifier->width - filled;
	if (specifier->zero_padding == TRUE && specifier->precision == NO_VALUE
		&& specifier->left_justify == FALSE)
		padding_char = ZEROPAD_SYMBOL;
	else
		padding_char = BLANK_SYMBOL;
	padding = (char *)malloc(sizeof(char) * (padding_len + 1));
	if (!padding)
		return (NULL);
	padding[padding_len] = '\0';
	while (padding_len--)
		padding[padding_len] = padding_char;
	return (padding);
}

char	*merge_string_helper(int count, ...)
{
	va_list	ap;
	int		i;
	char	*s;
	char	*temp;
	char	*result;

	i = 0;
	result = NULL;
	va_start(ap, count);
	while (i++ < count)
	{
		s = va_arg(ap, char *);
		temp = result;
		result = ft_strjoin(result, s);
		if (!result)
		{
			free(temp);
			va_end(ap);
			return (NULL);
		}
		free(temp);
	}
	va_end(ap);
	return (result);
}

char	*merge_strings(t_specifier *specifier, char *prefix,
					char *num_char, char *padding)
{
	char	*result_str;

	result_str = NULL;
	if (!prefix || !num_char || !padding)
	{
		free_strs(3, &prefix, &num_char, &padding);
		return (NULL);
	}
	if (*padding == ZEROPAD_SYMBOL)
		result_str = merge_string_helper(3, prefix, padding, num_char);
	else
	{
		if (specifier->left_justify)
			result_str = merge_string_helper(3, prefix, num_char, padding);
		else
			result_str = merge_string_helper(3, padding, prefix, num_char);
	}
	return (result_str);
}

int	print_num(t_specifier *specifier, long long int num)
{
	int		print_count;
	char	*prefix;
	char	*num_char;
	char	*padding;
	char	*result_str;

	result_str = NULL;
	prefix = get_prefix(specifier, num);
	num_char = convert_num(specifier, num);
	padding = get_padding(specifier, ft_strlen(prefix) + ft_strlen(num_char));
	result_str = merge_strings(specifier, prefix, num_char, padding);
	if (result_str == NULL)
	{
		free_strs(3, &prefix, &num_char, &padding);
		return (OPERATION_ERROR);
	}
	print_count = write(STDOUT_FILENO, result_str, ft_strlen(result_str));
	free_strs(3, &prefix, &num_char, &padding);
	free(result_str);
	return (print_count);
}
