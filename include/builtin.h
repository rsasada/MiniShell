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

void	ft_chdir(char *path);
void	ft_env(t_app *app, t_list *arg);

void	print_env(t_app *app, int is_export);
void	ft_unset(t_app *app, t_list *argv, pid_t *pid);
#endif
