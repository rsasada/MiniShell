/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:18:58 by jongykim          #+#    #+#             */
/*   Updated: 2024/01/14 13:18:58 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../include/minishell.h"

typedef struct s_ast_node t_ast_node;
typedef enum e_node_type t_node_type;

enum e_node_type {
	NODE_PIPELINE,
	NODE_CMD,
	NODE_SIMPLE_CMD,
	NODE_ARG_LIST,
	NODE_REDIRECTION,
	NODE_FILENAME,
	NODE_FILEPATH
};

struct s_ast_node {
	t_node_type node_type;
	union {
		struct {
			t_ast_node *left;
			t_ast_node *right;
		} s_pipeline;
		struct {
			t_ast_node *simple_cmd;
			t_ast_node *redirection;
		} s_cmd;
		struct {
			t_ast_node *file_path;
			t_ast_node *args;
		} s_simple_cmd;
        t_list *arg_list;
		struct {
			char *op;
			t_ast_node *file_name;
		} s_redirection;
		char *file_name_val;
		char *file_path_val;
	} u_node_data;
};

// tempo construct for test
typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT
} t_token_type;

typedef struct s_token {
	t_token_type type;
	char *value;
} t_token;

t_ast_node *parse_pipeline(t_list **cur_token);
t_ast_node *parse_cmd(t_list **cur_token);
t_ast_node *parse_simple_cmd(t_list **cur_token);
t_ast_node *parse_redirect(t_list **cur_token);
t_ast_node *parse_io_redirect(t_list **cur_token);

t_ast_node *create_cmd_node(t_ast_node *simple_cmd, t_ast_node *redirection);
t_ast_node *create_pipeline_node(t_ast_node *left, t_ast_node *right);
t_ast_node *create_redirection_node(char *op, t_ast_node *file_name_node);
t_ast_node *create_file_path_node(char *file_path);
t_ast_node *create_file_name_node(char *file_path);
t_ast_node *create_simple_cmd_node(t_ast_node *file_path_node, t_ast_node *arg_list);
t_ast_node *create_arg_list_node();
int accept_pipe(t_list *cur_token);
int accept_redirect(t_list *cur_token);
int accept_word(t_list *cur_token);
#endif
