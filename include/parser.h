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

# include "minishell.h"

# define HERE_DOC_MAX 128
# define PARSE_OK 0
# define SYNTAX_ERROR -1

typedef struct s_ast_node	t_ast_node;
typedef enum e_node_type	t_node_type;

enum e_node_type
{
	NODE_PIPELINE,
	NODE_CMD,
	NODE_SIMPLE_CMD,
	NODE_ARG_LIST,
	NODE_REDIRECTION,
	NODE_FILENAME,
	NODE_FILEPATH
};

struct s_ast_node
{
	t_node_type	node_type;
	union
	{
		struct
		{
			t_ast_node	*left;
			t_ast_node	*right;
		} s_pipeline;
		struct
		{
			t_ast_node	*simple_cmd;
			t_ast_node	*redirection;
		} s_cmd;
		struct
		{
			t_ast_node	*file_path;
			t_ast_node	*args;
		} s_simple_cmd;
		t_list	*arg_list;
		struct
		{
			char		*op;
			t_ast_node	*file_name;
		} s_redirection;
		char	*file_name_val;
		char	*file_path_val;
	} u_node_data;
};

//parse_main.c
t_ast_node	*ast_parser(t_list **token_list);

//parse_pipeline.c
t_ast_node	*parse_pipeline(t_list **cur_token, int *error_code);
t_ast_node	*create_pipeline_node(t_ast_node *left, t_ast_node *right);
void		free_pipeline_node(t_ast_node *node);

//parse_cmd.c
t_ast_node	*parse_cmd(t_list **cur_token, int *error_code);
t_ast_node	*create_cmd_node(t_ast_node *simple_cmd, t_ast_node *redirection);
void		free_cmd_node(t_ast_node *node);

//parse_simple_cmd.c
t_ast_node	*parse_simple_cmd(t_list **cur_token);
t_ast_node	*create_simple_cmd_node(t_ast_node *file_path_node, \
		t_ast_node *arg_list);
void		free_simple_cmd_node(t_ast_node *node);

//parse_redirect.c
t_ast_node	*parse_redirect(t_list **cur_token, int *error_code);
t_ast_node	*create_redirection_node(char *op, t_ast_node *file_name_node);
void		free_redirection_node(t_ast_node *node);

//parse_io_redirect.c
t_ast_node	*parse_io_redirect(t_list **cur_token, int *error_code);

//parse_here_doc.c
t_ast_node	*parse_here_doc(t_list **cur_token);

//parse_argv.c
t_ast_node	*parse_argv(t_list **cur_token);
t_ast_node	*create_arg_list_node(void);
void		free_arg_list_node(t_ast_node *node);

//parse_helper.c
int			accept_pipe(t_list *cur_token);
int			accept_redirect(t_list *cur_token);
int			accept_word(t_list *cur_token);

//node_constructor.c
t_ast_node	*create_file_path_node(char *file_path);
t_ast_node	*create_file_name_node(char *file_path);

int			is_valid_env_char(char c);
char		*copy_char_to_result(char *result, char c, size_t *len);
void		free_ast(void *content);

void		expand_env(t_app *app, t_list **tokens);
char		*expand_env_helper(t_app *app, const char *value, \
int *i, size_t *len);
void		remove_quote(t_list *token);
void		consume_token(t_list **cur_token);
#endif
