/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:20:29 by jongykim          #+#    #+#             */
/*   Updated: 2024/01/14 16:20:29 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int is_expected(t_list *cur_token, t_token_type expected_type) {
    if (((t_token *) cur_token->content)->type == expected_type)
        return (1);
    else
        return (0);
}

int accept_pipe(t_list *cur_token)
{
    return (is_expected(cur_token, TOKEN_PIPE));
}

int accept_redirect(t_list *cur_token)
{
    return (is_expected(cur_token, TOKEN_REDIRECT));
}

int accept_word(t_list *cur_token)
{
    return (is_expected(cur_token, TOKEN_WORD));
}