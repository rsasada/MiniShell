/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:23:20 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:40:42 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(const char *str)
{
	size_t	len;
	long	result;

	len = ft_strlen(str);
	result = write(1, str, len);
	return (result);
}

int	print_with_padding(t_specifier *specifier, char *padding, int c)
{
	int	print_count;

	print_count = 0;
	if (specifier->left_justify)
	{
		print_count += ft_putchar(c);
		print_count += ft_putstr(padding);
	}
	else
	{
		print_count += ft_putstr(padding);
		print_count += ft_putchar(c);
	}
	return (print_count);
}

int	print_char(t_specifier *specifier, int c)
{
	int		spaces;
	int		print_count;
	int		i;
	char	pad_char;
	char	*padding;

	spaces = specifier->width - 1;
	if (specifier -> left_justify == FALSE && specifier->zero_padding == TRUE)
		pad_char = ZEROPAD_SYMBOL;
	else
		pad_char = BLANK_SYMBOL;
	padding = malloc(sizeof(char) * (spaces + 1));
	if (!padding)
		return (OPERATION_ERROR);
	i = 0;
	while (i < spaces)
		padding[i++] = pad_char;
	padding[i] = '\0';
	print_count = print_with_padding(specifier, padding, c);
	free(padding);
	return (print_count);
}

int	print_str(t_specifier *specifier, char *str)
{
	size_t		len;
	int			res;
	int			print_count;
	char		*buffer;

	if (!str)
		str = NULL_SYMBOL;
	len = ft_strlen(str);
	if ((int) len < 0)
		return (OPERATION_ERROR);
	if (specifier -> width == 0 && specifier -> precision == 0)
		return (0);
	if (specifier->precision >= 0 && specifier->precision < (int)len)
		len = specifier->precision;
	buffer = ft_substr(str, 0, len);
	if (!buffer)
		return (OPERATION_ERROR);
	if (append_padding(specifier, &buffer) < 0)
		free_buf_with_error(&buffer);
	print_count = ft_strlen(buffer);
	res = write(STDOUT_FILENO, buffer, print_count);
	free(buffer);
	if (res < 0)
		return (res);
	return (print_count);
}
