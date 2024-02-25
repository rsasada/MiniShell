/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:21:53 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/25 22:09:43 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include <fcntl.h>

int	g_exit_code;

typedef struct s_app
{
	t_list	*env_lst;
	t_list	*pid_storage;
}	t_app;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

// error.c
void	exit_with_error(char *error_message);
void	*print_syntax_error(char *error, int *error_code);

// init_signal.c
void	config_signal(void);

//env.c
void	init_env(t_app *app, char **envp);
t_list	*find_env(t_list **env_list, char *key);

// libft_extension
void	*ft_realloc(void *ptr, size_t size);

#endif
