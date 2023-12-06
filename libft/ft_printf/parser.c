/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:19:28 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:40:26 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	append_plain_text(t_list **fmt_specifiers, char *head, char *tail)
{
	t_specifier	*specifier;
	t_list		*node;

	specifier = create_specifier ();
	if (!specifier)
		return (OPERATION_ERROR);
	specifier->fmt_type = PLAIN_FORMAT;
	specifier->start = head;
	specifier->end = tail;
	node = ft_lstnew (specifier);
	if (!node)
	{
		free (specifier);
		return (OPERATION_ERROR);
	}
	ft_lstadd_back (fmt_specifiers, node);
	return (OPERATION_SUCCESS);
}

static int	append_specifier(t_list **lst, t_specifier *sp, char *p, char **fmt)
{
	t_list	*node;

	sp->start = p;
	sp->end = *fmt;
	node = ft_lstnew (sp);
	if (!node)
	{
		free (node);
		return (OPERATION_ERROR);
	}
	ft_lstadd_back (lst, node);
	return (OPERATION_SUCCESS);
}

static int	read_format(t_list **fmt_specifiers, char **fmt)
{
	t_specifier	*new_specifier;
	char		*p;

	new_specifier = create_specifier();
	if (!new_specifier)
		return (OPERATION_ERROR);
	p = *fmt;
	read_flags (new_specifier, fmt);
	read_minwidth (new_specifier, fmt);
	read_precision (new_specifier, fmt);
	if (read_types (new_specifier, fmt) != OPERATION_SUCCESS)
	{
		free (new_specifier);
		return (OPERATION_ERROR);
	}
	return (append_specifier (fmt_specifiers, new_specifier, p, fmt));
}

int	parse_formats(t_list **fmt_specifiers, const char *fmt)
{
	char	*p;
	char	*plain_text;

	p = (char *) fmt;
	while (*p)
	{
		if (*p == '%')
		{
			if (read_format (fmt_specifiers, &p) == OPERATION_ERROR)
				return (OPERATION_ERROR);
		}
		else
		{
			plain_text = p;
			while (*p && *p != '%')
				p++;
			if (append_plain_text(fmt_specifiers, plain_text, p)
				== OPERATION_ERROR)
				return (OPERATION_ERROR);
		}
	}
	return (OPERATION_SUCCESS);
}
