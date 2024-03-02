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

bool	check_option(char **args);
char	**get_args(t_ast_node *simple_cmd);

int	ft_echo(t_app *app, t_ast_node *simple_cmd)
{
	size_t	i;
	bool	option_flag;
	char	**args;

	(void)app;
	args = get_args(simple_cmd);
	option_flag = check_option(args);
	if (option_flag == true)
		i = 2;
	else
		i = 1;
	while (args[i] != NULL)
	{
		if ((option_flag == false && i != 1)
			|| (option_flag == true && i != 2))
			write(1, " ", 1);
		ft_putstr_fd(args[i], 1);
		i ++;
	}
	if (option_flag == false)
		write(1, "\n", 1);
	return (0);
}

bool	check_option(char **args)
{
	size_t	i;
	char	option;

	i = 2;
	option = 'n';
	if (args[1] != NULL && ft_strncmp(args[1], "-n", 2) == 0)
	{
		while (args[1][i] != '\0')
		{
			if (args[1][i] != option)
				return (false);
			i ++;
		}
		return (true);
	}
	return (false);
}
