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

void reorder_tokens(t_list **head) {
    t_list *cur;
    t_list *prev;

    prev = NULL;
    cur = *head;
    while ((cur != NULL && cur->next == NULL) && !accept_pipe(cur)) {
        if (accept_redirect(cur) && accept_word(cur->next)) {
            prev = cur->next;
            cur = cur->next->next;
        } else if (accept_word(cur)) {
            if (prev != NULL) {
                prev->next = cur->next;
                cur->next = *head;
                *head = cur;
            }
            break;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
}

char *create_temp_file() {
    char filename[256];
    char *num_str;
    int fd;
    int count;
    char *ret;

    count = 0;
    while (count < HERE_DOC_MAX) {
        count++;
        num_str = ft_itoa(count);
        if (num_str == NULL)
            continue;
        ft_strlcpy(filename, "/tmp/here_doc_", 15);
        ft_strlcat(filename, num_str, 15 + ft_strlen(num_str));
        ft_strlcat(filename, ".tmp", 21 + ft_strlen(num_str));
        free(num_str);
        if (access(filename, F_OK) != -1)
            continue;
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            continue;
        else {
            close(fd);
            ret = (char *) malloc(sizeof(char) * (strlen(filename) + 1));
            if (!ret)
                return (NULL);
            ft_strlcpy(ret, filename, ft_strlen(filename) + 1);
            return (ret);
        }
    }
    return (NULL);
}

t_ast_node *parse_here_doc(t_list **cur_token) {
    char *limiter;
    char *line;
    char *filename;
    int fd;

    limiter = ((t_token *) (*cur_token)->content)->value;
    filename = create_temp_file();
    if (!filename)
        return (NULL);
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        exit_with_error("here_doc");
    while (1) {
        line = readline("heredoc> ");
        if (!line || ft_strncmp(line, limiter, ft_strlen(line)) == 0) {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    return (create_file_name_node(filename));
}

t_ast_node *parse_argv(t_list **cur_token) {
    t_ast_node *args_node;
    t_ast_node *arg_node;

    args_node = create_arg_list_node();
    while (*cur_token != NULL && accept_word(*cur_token)) {
        arg_node = create_file_name_node(((t_token *) (*cur_token)->content)->value);
        if (!arg_node) {
            return (NULL);
        }
        *cur_token = (*cur_token)->next;
        append_arg(args_node, arg_node);
    }
    return (args_node);
}

t_ast_node *parse_io_redirect(t_list **cur_token, int *error_code) {
    t_token *token;
    char *op;
    t_ast_node *file_name_node;

    if (*cur_token == NULL)
        return (NULL);
    op = NULL;
    token = (t_token *) (*cur_token)->content;
    if (token->type != TOKEN_REDIRECT)
        return (NULL);
    op = token->value;
    *cur_token = (*cur_token)->next;
    if (*cur_token == NULL) {
        print_syntax_error("newline");
        *error_code = SYNTAX_ERROR;
        return (NULL);
    } else if (!accept_word(*cur_token)) {
        print_syntax_error(((t_token *) (*cur_token)->content)->value);
        *error_code = SYNTAX_ERROR;
        return (NULL);
    }
    if (ft_strncmp(op, "<<", 3) == 0) {
        file_name_node = parse_here_doc(cur_token);
    } else {
        file_name_node = create_file_name_node(((t_token *) (*cur_token)->content)->value);
    }
    if (!file_name_node)
        return (NULL);
    *cur_token = (*cur_token)->next;
    return (create_redirection_node(op, file_name_node));
}

t_ast_node *parse_redirect(t_list **cur_token, int *error_code) {
    t_ast_node *io_redirect;
    t_ast_node *redirect;

    if (*cur_token == NULL)
        return (NULL);
    io_redirect = parse_io_redirect(cur_token, error_code);
    if (!io_redirect)
        return (NULL);
    if (*cur_token && accept_redirect(*cur_token)) {
        redirect = parse_redirect(cur_token, error_code);
        if (!redirect) {
            return (NULL);
        }
        return create_pipeline_node(io_redirect, redirect); // TODO : use pipeline or make new function
    }
    return (io_redirect);
}

t_ast_node *parse_simple_cmd(t_list **cur_token) {
    t_ast_node *file_path_node;
    t_ast_node *argv_node;

    if (*cur_token == NULL || !accept_word(*cur_token)) {
        return (NULL);
    }
    file_path_node = create_file_path_node(((t_token *) (*cur_token)->content)->value);
    *cur_token = (*cur_token)->next;
    if (*cur_token != NULL && accept_word(*cur_token)) {
        argv_node = parse_argv(cur_token);
        if (!argv_node) {
            return (NULL);
        }
        return create_simple_cmd_node(file_path_node, argv_node);
    }
    return create_simple_cmd_node(file_path_node, NULL);
}

t_ast_node *parse_cmd(t_list **cur_token, int *error_code) {
    t_ast_node *simple_cmd;
    t_ast_node *redirection;

    if (cur_token == NULL || *cur_token == NULL)
        return (NULL);
    simple_cmd = parse_simple_cmd(cur_token);
    redirection = NULL;
    if (*cur_token != NULL && accept_redirect(*cur_token))
        redirection = parse_redirect(cur_token, error_code);
    if (simple_cmd == NULL && redirection == NULL)
        return (NULL);
    return (create_cmd_node(simple_cmd, redirection));
}

t_ast_node *parse_pipeline(t_list **cur_token, int *error_code) {
    t_ast_node *left;
    t_ast_node *right;
    t_ast_node *pipe_node;

    if (cur_token == NULL || *cur_token == NULL)
        return (NULL);
    reorder_tokens(cur_token);
    left = parse_cmd(cur_token, error_code);
    if (left == NULL)
        return (NULL);
    if ((*cur_token) != NULL && accept_pipe(*cur_token)) {
        *cur_token = (*cur_token)->next;
        if (*cur_token == NULL) {
            print_syntax_error("newline");
            *error_code = SYNTAX_ERROR;
            return (NULL);
        }
        right = parse_pipeline(cur_token, error_code);
        if (right == NULL) {
            return (NULL);
        }
        pipe_node = create_pipeline_node(left, right);
        left = pipe_node;
    }
    return (left);
}
