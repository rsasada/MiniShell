/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:30:08 by risasada          #+#    #+#             */
/*   Updated: 2024/03/07 19:30:11 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	redirect_input_to_pipe(int *pipe_fd)
{
	if (pipe_fd == NULL)
		return ;
	dup2(pipe_fd[0], STDIN_FILENO);
	close_pipe(pipe_fd);
}

void	redirect_output_to_pipe(int *pipe_fd)
{
	if (pipe_fd == NULL)
		return ;
	dup2(pipe_fd[1], STDOUT_FILENO);
	close_pipe(pipe_fd);
}

void	close_pipe(int	*fd)
{
	if (fd == NULL)
		return ;
	close(fd[0]);
	close(fd[1]);
}

void	prepare_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	wait_child(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	g_exit_code = WEXITSTATUS(status);
	if (WIFEXITED(status) == 0)
	{
		if (WTERMSIG(status) >> 4 == SIGQUIT)
			ft_putstr_fd("Quit: 3", STDERR_FILENO);
		else
			ft_putendl_fd("", STDERR_FILENO);
	}
}
