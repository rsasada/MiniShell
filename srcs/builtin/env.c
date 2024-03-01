/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:20:50 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/12 14:20:50 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_env(t_app *app, t_list *arg) {
	t_list *env_list;
	t_list *cur;

	if (arg) {
		g_exit_code = 1;
		ft_putendl_fd("push: too many arguments", 2);
		return;
	}
	env_list = app->env_lst;
	cur = env_list;
	while (cur) {
		printf("%s", ((t_env *) (cur->content))->key);
		printf("=");
		printf("%s", ((t_env *) (cur->content))->value);
		printf("\n");
		cur = cur->next;
	}
	g_exit_code = 0;
}

//int main() {
//	t_app *app;
//
//	app = (t_app *) malloc(sizeof(t_app));
//	t_env e1 = {.key="env1", .value= "test1"};
//	t_env e2 = {.key="env2", .value= "test2"};
//	t_env e3 = {.key="env3", .value= ""};
//	t_env e4 = {.key="env4", .value= "test4"};
//	t_env e5 = {.key="env5", .value= ""};
//	t_list *env_list = NULL;
//	ft_lstadd_back(&env_list, ft_lstnew(&e1));
//	ft_lstadd_back(&env_list, ft_lstnew(&e2));
//	ft_lstadd_back(&env_list, ft_lstnew(&e3));
//	ft_lstadd_back(&env_list, ft_lstnew(&e4));
//	ft_lstadd_back(&env_list, ft_lstnew(&e5));
//
//	app->env_lst = env_list;
//	t_list *arg = env_list;
//	ft_env(app, arg);
//	free(app);
//	printf("%d", g_exit_code);
//	return (0);
//}