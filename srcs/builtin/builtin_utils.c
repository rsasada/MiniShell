/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:45:19 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/20 23:45:19 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_chdir(char *path)
{
    if(chdir(path) == -1)
    {
        ft_putstr_fd("push: cd:", STDERR_FILENO);
        perror(path);
        g_exit_code = EXIT_FAILURE;
        return;
    }
}