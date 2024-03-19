/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:23:39 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/20 22:23:39 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H

# define EXECUTION_H

# include "minishell.h"
# include "parser.h"

# define NO_PIPE -10

void	close_pipe(int	*fd);
void	redirect_output_to_pipe(int *pipe_fd);
void	redirect_input_to_pipe(int	*pipe_fd);
void	prepare_pipe(int *pipe_fd);
void	add_pid_storage(t_list *pid_storage, pid_t child_pid);

void	process_redirects(t_ast_node *s_r);
void	execute(t_ast_node *ast, t_app *app);

char	**convert_env_to_char(t_list *env_list);
char	**split_env_path(t_list *env_list);
char	*get_cmd_path(t_ast_node *file_node, char **env_path);
void	validate_cmd_path(char *cmd_path, t_ast_node *cmd_node);

bool	check_builtin_cmd(t_ast_node *simple_cmd);
int		builtin_functions(t_ast_node *simple_cmd, t_app *app);
int		execute_single_builtin_cmd(t_ast_node *cmd, t_app *app);
void	wait_child(int pid);
#endif