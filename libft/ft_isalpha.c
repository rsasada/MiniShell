/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:00:58 by jongykim          #+#    #+#             */
/*   Updated: 2023/05/21 18:05:31 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isupper(int c)
{
	unsigned char	ch;

	ch = (unsigned char) c;
	return (ch >= 'A' && ch <= 'Z');
}

static int	ft_islower(int c)
{
	unsigned char	ch;

	ch = (unsigned char) c;
	return (ch >= 'a' && ch <= 'z');
}

int	ft_isalpha(int c)
{
	unsigned char	ch;

	if (c < 0 || c > 255)
		return (0);
	ch = (unsigned char) c;
	return (ft_isupper(ch) || ft_islower(ch));
}
