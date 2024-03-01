/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:24:23 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/23 00:24:23 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_pwd(void)
{
    char *cwd;

    cwd = getcwd(NULL,0);
    if(!cwd)
        exit_with_error("getcwd");
    ft_putendl_fd(cwd, STDOUT_FILENO);
    free(cwd);
}