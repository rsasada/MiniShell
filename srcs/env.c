/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:15:51 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/14 01:15:51 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_env(t_env *env, char **envp, int i)
{
	char	*delimit;
	char	*key;
	char	*value;

	key = envp[i];
	delimit = ft_strchr(envp[i], '=');
	*delimit = '\0';
	value = delimit + 1;
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
}

void	init_env(t_app *app, char **envp)
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

t_list	*find_env(t_list **env_list, char *key)
{
	t_list	*cur;
	char	*env_key;

	cur = *env_list;
	while (cur != NULL)
	{
		env_key = ((t_env *)(cur->content))->key;
		if (ft_strncmp(env_key, key, ft_strlen(key) + 1) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void	add_env(t_list **env_list, char *key, char *value)
{
	t_env	*temp;

	temp = (t_env *)malloc(sizeof(t_env));
	if (!temp)
		exit_with_error("malloc");
	temp->key = ft_strdup(key);
	temp->value = ft_strdup(value);
	remove_env(env_list, key);
	ft_lstadd_back(env_list, ft_lstnew(temp));
}

void	remove_env(t_list **env_list, char *arg)
{
	t_list	*cur;
	t_list	*prev;
	char	*env;

	cur = *env_list;
	prev = NULL;
	while (cur != NULL)
	{
		env = ((t_env *)(cur->content))->key;
		if (ft_strncmp(env, arg, ft_strlen(arg) + 1) == 0)
		{
			if (prev == NULL)
				*env_list = cur->next;
			else
				prev->next = cur->next;
			ft_lstdelone(cur, free_env);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
