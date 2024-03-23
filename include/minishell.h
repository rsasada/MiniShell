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
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

//Error_message
# define PERM_DENIED ": Permission denied"
# define CMD_NOT_FOUND ": command not found"
# define FILE_NOT_FOUND ": No such file or directory"
# define IS_DIR ": is a directory"

extern int	g_exit_code;

typedef struct s_app
{
	t_list	*env_lst;
	t_list	*pid_storage;
	char	*home_path;
}	t_app;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef enum signal_type
{
	EXECUTE_HEREDOC,
	PARENT,
	CHILD,
	SHELL_LOOP,
}	t_signal_type;

// error.c
void	exit_with_error(char *error_message);
void	custom_error(int defined_code, char *error_message, char *cmd);
void	*print_syntax_error(char *error, int *error_code);
void	handling_error(char *error_message, int exit_code);

// init_signal.c
void	config_signal(t_signal_type	type);

//env.c
void	init_env(t_app *app, char **envp);
t_list	*find_env(t_list **env_list, char *key);

// libft_extension
void	ft_merge_list_at(t_list **first_list, \
		t_list **second_list, int position);

void	remove_env(t_list **env_list, char *arg);
void	free_env(void *env);
void	add_env(t_list **env_list, char *key, char *value);

void	free_token(void *token);
void	free_strings(char **strings);
char	*realloc_str(char *str, size_t size);

#endif
