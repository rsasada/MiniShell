/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/14 03:54:11 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "parser.h"

void	ft_chdir(char *path);
void	print_env(t_app *app, int is_export);
int		ft_cd(t_app *app, t_list *argv);
int		ft_env(t_app *app, t_list *argv);
int		ft_unset(t_app *app, t_list *argv);
int		ft_export(t_app *app, t_list *argv);
int		ft_pwd(t_app *app, t_list *argv);
int		ft_exit(t_app *app, t_list *argv);
int		ft_echo(t_app *app, t_ast_node *simple_cmd);

#endif
