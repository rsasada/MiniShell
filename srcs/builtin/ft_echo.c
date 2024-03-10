/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risasada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:58:53 by risasada          #+#    #+#             */
/*   Updated: 2024/03/02 17:35:23 by risasada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

bool	check_option(char *arg);
char	**get_args(t_ast_node *simple_cmd);

int	ft_echo(t_app *app, t_ast_node *simple_cmd)
{
	size_t	i;
	bool	option_flag;
	char	**args;

	(void)app;
	i = 1;
	args = get_args(simple_cmd);
	option_flag = check_option(args[1]);
	while (check_option(args[i]) == true)
		i ++;
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			write(1, " ", 1);
		i ++;
	}
	if (option_flag == false)
		write(1, "\n", 1);
	return (1);
}

bool	check_option(char *arg)
{
	size_t	i;
	char	option;

	i = 2;
	option = 'n';
	if (arg != NULL && ft_strncmp(arg, "-n", 2) == 0)
	{
		while (arg[i] != '\0')
		{
			if (arg[i] != option)
				return (false);
			i ++;
		}
		return (true);
	}
	return (false);
}
