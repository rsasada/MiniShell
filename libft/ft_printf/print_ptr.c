/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:15:26 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:40:59 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	get_ptr_len(void *ptr)
{
	unsigned char	*cursor;
	int				len;

	len = sizeof(ptr) * 2;
	cursor = (unsigned char *)(&ptr) + sizeof(ptr) - 1;
	while (len > 0)
	{
		if (*cursor / 16 != 0)
			break ;
		len--;
		if (*cursor % 16 != 0)
			break ;
		len--;
		cursor--;
	}
	return (len);
}

static void	ptr_to_hex(void *ptr, int len_ptr, char *buf)
{
	unsigned char	*cursor;
	int				i;

	cursor = (unsigned char *)(&ptr) + sizeof(ptr) - 1;
	i = len_ptr - (sizeof(ptr) * 2);
	while (i < len_ptr)
	{
		if (i >= 0)
			buf[i] = LHEX_CHARSET[*cursor / 16];
		i++;
		if (i >= 0)
			buf[i] = LHEX_CHARSET[*cursor % 16];
		i++;
		cursor--;
	}
	buf[len_ptr] = '\0';
}

static char	*get_ptr_as_ascii(t_specifier *specifier, void *ptr)
{
	char	*buf;
	int		len_ptr;

	if (ptr == NULL)
	{
		if (specifier->precision != NO_VALUE)
			return (ft_strdup(""));
		else
			return (ft_strdup("0"));
	}
	len_ptr = get_ptr_len(ptr);
	buf = (char *) malloc(len_ptr + 1);
	if (!buf)
		return (NULL);
	ptr_to_hex(ptr, len_ptr, buf);
	return (buf);
}

static char	*get_ptr_prefix(t_specifier *specifier, int len_ptr)
{
	int		res;
	char	*buf;
	char	*temp;

	buf = ft_strdup(LHEX_PREFIX);
	if (!buf)
		return (NULL);
	if (specifier->precision != NO_VALUE && specifier->precision > len_ptr)
	{
		temp = append_pad_for_prefix(specifier->precision - len_ptr,
				ZEROPAD_SYMBOL);
		if (!temp)
		{
			free(buf);
			return (NULL);
		}
		res = append_str(&buf, temp);
		free(temp);
		if (res < 0)
			return (NULL);
	}
	return (buf);
}

int	print_ptr(t_specifier *specifier, void *ptr)
{
	int		print_count;
	char	*prefix;
	char	*address;
	char	*padding;
	char	*result_str;

	prefix = get_ptr_prefix(specifier, get_ptr_len(ptr));
	address = get_ptr_as_ascii(specifier, ptr);
	padding = get_padding(specifier, ft_strlen(prefix) + ft_strlen(address));
	result_str = merge_strings(specifier, prefix, address, padding);
	if (result_str == NULL)
	{
		free_strs(3, &prefix, &address, &padding);
		return (OPERATION_ERROR);
	}
	print_count = write(STDOUT_FILENO, result_str, ft_strlen(result_str));
	free_strs(3, &prefix, &address, &padding);
	free(result_str);
	return (print_count);
}
