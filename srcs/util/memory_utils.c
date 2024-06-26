/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 03:35:07 by jongykim          #+#    #+#             */
/*   Updated: 2024/01/28 03:35:07 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/lexer.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *) content;
	if (token != NULL)
	{
		free(token->value);
		free(token);
	}
}

void	free_env(void *env)
{
	t_env	*e;

	if (env != NULL)
	{
		e = (t_env *) env;
		free(e->key);
		free(e->value);
		free(e);
	}
}

void	free_strings(char **strings)
{
	int	i;

	if (!strings)
		return ;
	i = 0;
	while (strings[i] != NULL)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}
