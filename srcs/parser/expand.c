/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 00:18:46 by jongykim          #+#    #+#             */
/*   Updated: 2024/01/23 00:18:46 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void replace_tokens(t_list **old, t_list *node_to_change, t_list *new) {
    t_list *next;
    t_list *prev;

    next = node_to_change->next;
    ft_lstadd_back(&new, next);
    if (node_to_change == *old) {
        *old = new;
    } else {
        prev = *old;
        while (prev->next != node_to_change)
            prev = prev->next;
        prev->next = new;
    }
    ft_lstdelone(node_to_change, free_token);
}

int expand_env_helper(char **result, const char *value, int i, int *len) {
    int var_name_start;
    char *var_name;
    char *var_value;
    int var_len;
    int var_value_len;

    var_len = 0;
    var_name_start = i + 1;
    while (ft_isalnum(value[var_name_start + var_len]) || value[var_name_start + var_len] == '_')
        var_len++;
    var_name = malloc(sizeof(var_len + 1));
    if (!var_name)
        return (-1);
    ft_strlcpy(var_name, value + var_name_start, var_len + 1);
    var_value = getenv(var_name);
    free(var_name);
    if (var_value) {
        var_value_len = ft_strlen(var_value);
        *result = ft_realloc(*result, *len + var_value_len + 1);
        if (!*result)
            return (-1);
        ft_strlcpy(*result + *len, var_value, var_value_len + 1);
        *len += var_value_len;
    } else {
        *result = ft_realloc(*result, *len + 1);
        if (!*result)
            return (-1);
        (*result)[*len] = '\0';
        *len += 1;
    }
    return (i + var_len + 1);
}

char *expand_token_value(const char *value) {
    char *result;
    int i;
    int len;
    int quote_flag;

    if (!value)
        return (NULL);
    i = 0;
    len = 0;
    quote_flag = 0;
    result = NULL;
    while (value[i] != '\0') {
        if (value[i] == '\"') {
            quote_flag = !quote_flag;
            i++;
            continue;
        }
        if (value[i] == '$' && (!quote_flag || value[i + 1] == '?')) {
            i = expand_env_helper(&result, value, i, &len);
            if (i == -1) {
                free(result);
                return (NULL);
            }
        } else {
            len++;
            result = ft_realloc(result, len + 1);
            if (!result)
                return (NULL);
            result[len - 1] = value[i];
            result[len] = '\0';
            i++;
        }
    }
    return (result);
}

void expand_env(t_list **tokens) {
    t_list *cur;
    t_list *new;
    t_token *token;
    char *new_value;
    t_list *next;

    cur = *tokens;
    new = NULL;
    while (cur != NULL) {
        token = (t_token *) (cur->content);
        if (token && token->type == TOKEN_WORD) {
            new_value = expand_token_value(token->value);
            if (new_value) {
                new = tokenizer(new_value,1);
                if (new) {
                    next = cur->next;
                    replace_tokens(tokens, cur, new);
                    cur = next;
                    continue;
                }
                free(new_value);
            }
        }
        cur = cur->next;
    }
}