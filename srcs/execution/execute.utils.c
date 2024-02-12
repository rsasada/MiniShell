/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:35:42 by risasada          #+#    #+#             */
/*   Updated: 2024/02/02 18:35:44 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"
#include "../../include/parser.h"

void	redirect_input_to_pipe(int	*pipe_fd)
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
