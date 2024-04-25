/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:18:31 by jongykim          #+#    #+#             */
/*   Updated: 2023/12/10 19:18:31 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

void	exit_with_error(char *error_message)
{
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	custom_error(int exit_code, char *error_message, char *cmd)
{
	ft_putstr_fd("push: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit(exit_code);
}

void	handling_error(char *error_message, int exit_code)
{
	ft_putendl_fd(error_message, STDERR_FILENO);
	g_signal = exit_code;
}

void	*print_syntax_error(char *error, int *error_code)
{
	ft_putstr_fd("push: syntax error near unexpected token `", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd("`", 2);
	*error_code = SYNTAX_ERROR;
	return (NULL);
}

void	*adhoc_handle_newline_error(char *error, int *error_code, char *op)
{
	free(op);
	return (print_syntax_error(error, error_code));
}
