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

int	main()
{
	char	*line;

	line = NULL;
	load_banner();
	while (1)
	{
		if (line != NULL)
		{
			add_history(line);
			free(line);
		}
		line = readline("push-1.0 ");
		
	}
	return (0);
}