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

void	exit_with_error(char *error_message)
{
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	*print_syntax_error(char *error, int *error_code)
{
	ft_putstr_fd("push: syntax error near unexpected token `", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd("`", 2);
	*error_code = SYNTAX_ERROR;
	return (NULL);
}
