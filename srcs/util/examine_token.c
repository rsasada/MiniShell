/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   examine_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:17:48 by risasada          #+#    #+#             */
/*   Updated: 2024/03/09 18:17:53 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/lexer.h"

void	trim_token(t_list *token)
{
	char	*content;
	char	*tmp;

	if (token == NULL)
		return ;
	while (token != NULL)
	{
		content = (char *)token->content;
		if (content[0] == '\"')
		{
			tmp = ft_strtrim(content, "\'");
			free(content);
			content = tmp;
		}
		else if (content[0] == '\"')
		{
			tmp = ft_strtrim(content, "\"");
			free(content);
			content = tmp; 
		}
		token = token->next;
	}
	return ;
}