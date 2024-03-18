/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:20:17 by jongykim          #+#    #+#             */
/*   Updated: 2023/12/06 19:05:45 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/execution.h"
#include "../include/lexer.h"
#include "../include/builtin.h"

int	g_exit_code = 0;

void	load_banner(void)
{
	printf("\033[34m");
	printf("______                      _   _       _____ _   _      _ _ \n");
	printf("| ___ \\                    | | | |     /  ___| | | |    | | |\n");
	printf("| |_/ /____      _____ _ __| | | |_ __ \\ `--.| |_| | ___| | |\n");
	printf("|  __/ _ \\ \\ /\\ / / _ \\ '__| | | | '_ \\"\
	" `--. \\  _  |/ _ \\ | |\n");
	printf("| | | (_) \\ V  V /  __/ |  | |_| | |_) /\\__/ / | | |  __/ | |\n");
	printf("\\_|  \\___/ \\_/\\_/ \\___|_|   \\___/| .__/\\"\
	"____/\\_| |_/\\___|_|_|\n");
	printf("                                 | | by.Risasada & Jongykim\n");
	printf("                                 |_| ver 1.0\n");
	printf("\033[0m");
}

void	init_app(t_app *app, char **envp)
{
	ft_memset(app, 0, sizeof(t_app));
	init_env(app, envp);
	load_banner();
	config_signal();
}

void	handle_line(char *line, t_app *app)
{
	t_list		*tokens;
	t_ast_node	*root;

	add_history(line);
	tokens = tokenizer(line, 0);
	expand_env(app, &tokens);
	reorder_tokens(&tokens);
	root = ast_parser(&tokens);
	execute(root, app);
	ft_lstclear(&tokens, free_token);
	free_ast(root);
}

void	run_shell_loop(t_app *app)
{
	char	*line;

	while (1)
	{
		line = readline("push-1.0 ");
		if (line == NULL)
			ft_exit(NULL, NULL);
		handle_line(line, app);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_app	app;

	if (argc != 1)
		return (0);
	(void) argv;
	init_app(&app, envp);
	run_shell_loop(&app);
	return (0);
}
