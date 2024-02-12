#ifndef EXECUTION_H

# define EXECUTION_H

# include "minishell.h"
<<<<<<< HEAD
# include "parser.h"
# include <fcntl.h>

# define NO_PIPE -10

void	close_pipe(int	*fd);
void	redirect_output_to_pipe(int *pipe_fd);
void	redirect_input_to_pipe(int	*pipe_fd);
void	prepare_pipe(int *pipe_fd);

void	process_redirects(t_ast_node *s_r);
void	execute(t_ast_node *ast, t_app *app);
=======

# define NO_PIPE -10

void	redirect_input_to_pipe(int	*pipe_fd);
void	redirect_output_to_pipe(int *pipe_fd);
void	close_pipe(int	*fd);
>>>>>>> 5e14497a4aeaa3072d7b5ae226773715b93dabef

#endif 