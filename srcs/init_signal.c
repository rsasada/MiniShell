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

void	signal_handler(int signum);

void	config_signal(void)
{
	struct sigaction	new;
	struct sigaction	old;

	sigemptyset(&new.sa_mask);
	new.sa_handler = signal_handler;
	new.sa_flags = 0;
	if (-1 == sigaction(SIGINT, &new, &old))
		exit(1);
	if (-1 == sigaction(SIGTERM, &new, &old))
		exit(1);
	if (-1 == sigaction(SIGQUIT, &new, &old))
		exit(1);
}

void	signal_handler(int signum)
{
	pid_t	pid;

	config_signal();
	pid = waitpid(-1, NULL, WNOHANG);
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		if (pid == -1)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			write(1, "\n", 1);
	}
}
