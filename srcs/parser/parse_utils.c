/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:11:00 by jongykim          #+#    #+#             */
/*   Updated: 2024/01/14 16:11:00 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void append_arg(t_ast_node *args_node, t_ast_node *arg_node) {
    t_list *new_arg;
    if (!args_node)
        return;
    new_arg = ft_lstnew(arg_node);
    if (!new_arg)
        return;
    if (!args_node->u_node_data.arg_list) {
        args_node->u_node_data.arg_list = new_arg;
    } else {
        ft_lstadd_back(&args_node->u_node_data.arg_list, new_arg);
    }
}

t_ast_node *parse_argv(t_list **cur_token) {
    t_ast_node *args_node;
    t_ast_node *arg_node;

    args_node = create_arg_list_node();
    while (*cur_token != NULL && accept_word(*cur_token)) {
        arg_node = create_file_name_node(((t_token *) (*cur_token)->content)->value);
        if (!arg_node) {
            free_ast(args_node);
            return (NULL);
        }
        *cur_token = (*cur_token)->next;
        append_arg(args_node, arg_node);
    }
    return (args_node);
}

t_ast_node *parse_io_redirect(t_list **cur_token) {
    t_token *token;
    char *op;

    if (*cur_token == NULL)
        return (NULL);
    op = NULL;
    token = (t_token *) (*cur_token)->content;
    if (token->type == TOKEN_REDIRECT) {
        op = token->value;
        *cur_token = (*cur_token)->next;
        if (!*cur_token || !accept_word(*cur_token)) {
            print_syntax_error(op);
            return (NULL);
        }
    }
    t_ast_node *file_name_node = create_file_name_node(((t_token *) (*cur_token)->content)->value);
    if (!file_name_node)
        return (NULL);
    *cur_token = (*cur_token)->next;
    return create_redirection_node(op, file_name_node);
}

t_ast_node *parse_redirect(t_list **cur_token) {
    t_ast_node *io_redirect;
    t_ast_node *redirect;

    if (*cur_token == NULL)
        return (NULL);
    io_redirect = parse_io_redirect(cur_token);
    if (!io_redirect)
        return (NULL);
    if (*cur_token && accept_redirect(*cur_token)) {
        redirect = parse_redirect(cur_token);
        if (!redirect) {
            free_ast(io_redirect);
            return (NULL);
        }
        return create_pipeline_node(io_redirect, redirect); // TODO : use pipeline or make new function
    }
    return (io_redirect);
}

t_ast_node *parse_simple_cmd(t_list **cur_token) {
    t_ast_node *file_path_node;
    t_ast_node *argv_node;

    if (*cur_token == NULL || !accept_word(*cur_token))
        return (NULL);
    file_path_node = create_file_path_node(((t_token *) (*cur_token)->content)->value);
    *cur_token = (*cur_token)->next;
    if (*cur_token != NULL && accept_word(*cur_token)) {
        argv_node = parse_argv(cur_token);
        if (!argv_node) {
            free_ast(file_path_node);
            return (NULL);
        }
        return create_simple_cmd_node(file_path_node, argv_node);
    }
    return create_simple_cmd_node(file_path_node, NULL);
}

t_ast_node *parse_cmd(t_list **cur_token) {
    t_ast_node *simple_cmd;
    t_ast_node *redirection;

    if (cur_token == NULL || *cur_token == NULL)
        return (NULL);
    simple_cmd = parse_simple_cmd(cur_token);
    if (simple_cmd == NULL)
        return (NULL);
    redirection = NULL;
    if (*cur_token != NULL && accept_redirect(*cur_token)) {
        redirection = parse_redirect(cur_token);
        if (redirection == NULL) {
            free_ast(simple_cmd);
            return (NULL);
        }
    }
    return (create_cmd_node(simple_cmd, redirection));
}

t_ast_node *parse_pipeline(t_list **cur_token) {
    t_ast_node *left;
    t_ast_node *right;
    t_ast_node *pipe_node;

    if (cur_token == NULL || *cur_token == NULL)
        return (NULL);
    left = parse_cmd(cur_token);
    if (left == NULL)
        return (NULL);
    if ((*cur_token) != NULL && accept_pipe(*cur_token)) {
        *cur_token = (*cur_token)->next;
        if (*cur_token == NULL) {
            print_syntax_error("newline");
            free_ast(left); // TODO : if line is too long, set function that include free_ast and return NULL
            return (NULL);
        }
        right = parse_pipeline(cur_token);
        if (right == NULL) {
            free_ast(left);
            return (NULL);
        }
        pipe_node = create_pipeline_node(left, right);
        left = pipe_node;
    }
    return (left);
}
