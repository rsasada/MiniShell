/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 00:18:46 by jongykim          #+#    #+#             */
/*   Updated: 2024/03/05 01:38:59 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/lexer.h"

static void	init_variables(int *i, size_t *len, int *quote_flag, char **result)
{
	*quote_flag = 0;
	*i = 0;
	*len = 0;
	*result = NULL;
}

int	check_char_after_dollar(const char *value, int *i)
{
	if (ft_isdigit(value[*i + 1]))
	{
		*i += 2;
		return (0);
	}
	else if (!is_valid_env_char(value[*i + 1]) && value[*i + 1] != '?')
		return (0);
	else
		return (1);
}

char	*expand_token_value(t_app *app, const char *value)
{
	char	*temp;
	char	*result;
	int		i;
	size_t	len;
	int		quote_flag;

	if (!value)
		return (NULL);
	init_variables(&i, &len, &quote_flag, &result);
	while (i <= (int)ft_strlen(value) && value[i] != '\0')
	{
		if (value[i] == '\'')
			quote_flag = !(quote_flag);
		else if (value[i] == '$' && !quote_flag && \
		check_char_after_dollar(value, &i))
		{
			temp = expand_env_helper(app, value, &i, &len);
			result = ft_strjoin(result, temp);
			free(temp);
		}
		else
			result = copy_char_to_result(result, value[i], &len);
		i++;
	}
	return (result);
}

void	replace_new_value(t_list **tokens, t_list **old, char *new_value)
{
	t_list	*cur;
	t_list	*new;
	int		i;

	new = NULL;
	i = 0;
	if (new_value)
		new = tokenizer(new_value, 1);
	cur = *tokens;
	while (cur)
	{
		if (cur == *old)
		{
			ft_merge_list_at(tokens, &new, i);
			break ;
		}
		i++;
		cur = cur->next;
	}
}

void	expand_env(t_app *app, t_list **tokens)
{
	t_list	*cur;
	t_list	*temp;
	t_token	*token;
	char	*new_value;

	cur = *tokens;
	while (cur != NULL)
	{
		temp = cur->next;
		token = (t_token *)(cur->content);
		if (token && token->type == TOKEN_WORD)
		{
			new_value = expand_token_value(app, token->value);
			if (new_value)
				replace_new_value(tokens, &cur, new_value);
			else
				delete_token_from_list(tokens, cur);
		}
		cur = temp;
	}
}
