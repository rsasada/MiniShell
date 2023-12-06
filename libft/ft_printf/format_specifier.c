/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_specifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:52:50 by jongykim          #+#    #+#             */
/*   Updated: 2023/06/24 16:40:00 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	initialize_specifier(t_specifier *new)
{
	new->fmt_type = NO_VALUE;
	new->start = NULL;
	new->end = NULL;
	new->width = NO_VALUE;
	new->precision = NO_VALUE;
	new->left_justify = FALSE;
	new->zero_padding = FALSE;
	new->alternate_form = FALSE;
	new->blank_space = FALSE;
	new->sign_specified = FALSE;
	return (OPERATION_SUCCESS);
}

t_specifier	*create_specifier(void)
{
	t_specifier	*new;

	new = (t_specifier *) malloc(sizeof(t_specifier));
	if (!new)
		return (NULL);
	initialize_specifier(new);
	return (new);
}
