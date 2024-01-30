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

void load_banner()
{
	ft_printf("\033[34m");
	ft_printf("______                      _   _       _____ _   _      _ _ \n");
	ft_printf("| ___ \\                    | | | |     /  ___| | | |    | | |\n");
	ft_printf("| |_/ /____      _____ _ __| | | |_ __ \\ `--.| |_| | ___| | |\n");
	ft_printf("|  __/ _ \\ \\ /\\ / / _ \\ '__| | | | '_ \\ `--. \\  _  |/ _ \\ | |\n");
	ft_printf("| | | (_) \\ V  V /  __/ |  | |_| | |_) /\\__/ / | | |  __/ | |\n");
	ft_printf("\\_|  \\___/ \\_/\\_/ \\___|_|   \\___/| .__/\\____/\\_| |_/\\___|_|_|\n");
	ft_printf("                                 | | by.Risasada & Jongykim\n");
	ft_printf("                                 |_| ver 1.0\n");
	ft_printf("\033[0m");
}

void get_env(t_env *env, char **envp, int i)
{
	char *delimit;
	char *key;
	char *value;

	key = envp[i];
	delimit = ft_strchr(envp[i], '=');
	*delimit = '\0';
	value = delimit + 1;
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
}

void init_env(t_app *app, char **envp)
{
	int		i;
	t_env	*env_entry;

	i = 0;
	app->env_lst = NULL;
	while (envp[i])
	{
		env_entry = malloc(sizeof(t_env));
		if (!env_entry)
			exit_with_error("Malloc");
		env_entry->key = NULL;
		env_entry->value = NULL;
		get_env(env_entry, envp, i);
		ft_lstadd_back(&app->env_lst, ft_lstnew(env_entry));
		i++;
	}
}

int	main(int argc, char **argv, char**envp)
{
	t_app	app;
	char	*line;
    t_list *tokens;
    t_ast_node *root;

	if (argc != 1)
		return (0);
	(void) argv;
	ft_memset(&app, 0, sizeof(t_app));
	init_env(&app, envp);
	line = NULL;
	load_banner();
	config_signal();
	while (1)
	{
		line = readline("push-1.0 ");
		if (line == NULL || ft_strncmp(line,"exit",5)==0)
		{
			ft_printf("exit\n");
			exit(1);
		}
		else
		{
			add_history(line);
            tokens = tokenizer(line, 0);
            root = ast_parser(&tokens);
			print_tree(root, 0);

			free(line);
		}
	}
}
