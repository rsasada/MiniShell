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
void	heredoc_signal_handler(int signum);

void	config_signal(t_signal_type	type)
{
	if (type == SHELL_LOOP)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == EXECUTE_HEREDOC)
	{
		signal(SIGINT, heredoc_signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	sigint_handler(int signum)
{
	pid_t	pid;

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

void	heredoc_signal_handler(int signum)
{
	struct termios	oldt;
	struct termios	newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	(void)signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	rl_replace_line("", 0);
	rl_on_new_line();
	g_signal = 130;
}
