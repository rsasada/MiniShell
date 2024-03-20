/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:22:56 by risasada          #+#    #+#             */
/*   Updated: 2023/12/16 16:22:58 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int signum);

void	config_signal(t_signal_type	type)
{

	if (type == SHELL_LOOP)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == EXECUTE_HEREDOC)
	{
		signal(SIGINT, );
		signal(SIGQUIT, );
	}
	else if (type == PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
}

void	sigint_handler(int signum)
{
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	heredoc_signal_handler(int	signum)
{	

}