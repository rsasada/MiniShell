/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:17:50 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:39:17 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft.h"
# include <stdarg.h>

# define BLANK_SYMBOL ' '
# define ZEROPAD_SYMBOL '0'
# define PERCENT_SYMBOL '%'
# define NULL_SYMBOL "(null)"
# define DECIMAL_CHARSET "0123456789"
# define LHEX_CHARSET "0123456789abcdef"
# define UHEX_CHARSET "0123456789ABCDEF"
# define LHEX_PREFIX "0x"
# define UHEX_PREFIX "0X"
# define POSITIVE_SIGN "+"
# define NEGATIVE_SIGN "-"
# define BLANK_PREFIX " "
# define OPERATION_SUCCESS 0
# define OPERATION_ERROR -1
# define NO_VALUE -1
# define TRUE 1
# define FALSE 0
# define PLAIN_FORMAT 0

typedef struct s_fmt_specifiers {
	char	fmt_type;
	char	*start;
	char	*end;
	int		width;
	int		precision;
	int		left_justify;
	int		zero_padding;
	int		alternate_form;
	int		blank_space;
	int		sign_specified;
}	t_specifier;

int				ft_printf(const char *format, ...);
int				parse_formats(t_list **fmt_specifiers, const char *fmt);
int				print_format(t_list *lst, va_list ap);
t_specifier		*create_specifier(void);
int				read_flags(t_specifier *specifier, char **fmt);
void			read_minwidth(t_specifier *specifier, char **fmt);
void			read_precision(t_specifier *specifier, char **fmt);
int				read_types(t_specifier *specifier, char **fmt);
int				print_plain_text(t_specifier *specifier);
int				print_char(t_specifier *specifier, int c);
int				print_str(t_specifier *specifier, char *str);
int				print_num(t_specifier *specifier, long long int num);
char			*apply_sign(t_specifier *specifier, long long int num);
int				apply_hex_prefix(t_specifier *specifier,
					size_t num, char **buf);
int				apply_precision(t_specifier *specifier, size_t num, char **buf);
int				get_base_num(t_specifier *specifier);
void			free_strs(int count, ...);
char			*convert_num(t_specifier *specifier, long long int value);
int				append_str(char **des, char *src);
int				append_padding(t_specifier *specifier, char **buf);
int				get_num_len(long long int num, int base);
char			*get_padding(t_specifier *specifier, int filled);
char			*merge_strings(t_specifier *specifier, char *prefix,
					char *num_char, char *padding);
int				print_ptr(t_specifier *specifier, void *ptr);
void			*free_str(char **str);
int				free_buf_with_error(char **buf);
char			*append_pad_for_prefix(int padding_len, char symbol);
#endif
