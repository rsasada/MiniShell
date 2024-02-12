#ifndef EXECUTION_H

# define EXECUTION_H

# include "minishell.h"
# include "parser.h"
# include <fcntl.h>

# define NO_PIPE -10

void	close_pipe(int	*fd);
void	redirect_output_to_pipe(int *pipe_fd);
void	redirect_input_to_pipe(int	*pipe_fd);

void	process_redirects(t_ast_node *s_r);
void	execute(t_ast_node *ast);

#endif 