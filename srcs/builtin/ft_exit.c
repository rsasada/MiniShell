/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:06:09 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/21 22:06:09 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static int	is_overflow(char *code)
{
	unsigned long long	num;

	while (ft_isdigit(*code))
	{
		if (num > LLONG_MAX / 10 || \
		(num == LLONG_MAX / 10 && (*code - '0') > LLONG_MAX % 10))
			return (1);
		num = num * 10 + (*code - '0');
		code++;
	}
	return (0);
}

static int	is_num(char *code)
{
	char	*c;

	c = code;
	if (*c == '-' || *c == '+')
		c++;
	if (*c == '\0')
		return (0);
	while (c)
	{
		if (ft_isdigit(*c))
			return (0);
		c++;
	}
	return (1);
}

static void	exit_with_code(char *code)
{
	int	num_code;

	num_code = ft_atoi(code);
	printf("exit\n");
	exit((unsigned char) num_code);
}

void	ft_exit(t_app *app, t_list *argv)
{
	char	*first_arg;

	if (!argv)
		exit_with_code("0");
	first_arg = ((t_ast_node *)(argv->content))->u_node_data.file_name_val;
	if (is_num(first_arg) && is_overflow(first_arg))
	{
		printf("exit\n");
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(first_arg, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
	}
	else if (argv->next != NULL)
	{
		printf("exit\n");
		ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
	}
	else
		exit_with_code(first_arg);
}
