/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:21:14 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/29 01:33:02 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	toggle_quote(int *quote_flag, int *i)
{
	*quote_flag = !(*quote_flag);
	(*i)++;
}

char	*adjust_result(char *result, char c, int *len)
{
	char	*temp;

	temp = ft_realloc(result, *len + 2);
	if (!temp)
		exit_with_error("realloc");
	temp[*len] = c;
	(*len)++;
	temp[*len] = '\0';
	return (temp);
}
