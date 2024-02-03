#ifndef EXECUTION_H

# define EXECUTION_H

# include "minishell.h"

# define NO_PIPE -10

void	redirect_input_to_pipe(int	*pipe_fd);
void	redirect_output_to_pipe(int *pipe_fd);
void	close_pipe(int	*fd);

#endif 