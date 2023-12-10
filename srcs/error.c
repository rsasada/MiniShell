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

void exit_with_error(char *error_message)
{
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
