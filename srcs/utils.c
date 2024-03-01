
int	find_env(t_list *env_list, char *key)
{
	t_list	*cur;
	t_env	*env;

	cur = env_list;
	while (cur)
	{
		env = (t_env *) cur->content;
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (1);
		cur = cur->next;
	}
	return (0);
}
