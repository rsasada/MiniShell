/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:39:44 by jongykim          #+#    #+#             */
/*   Updated: 2023/05/20 12:37:31 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	unsigned char	ch;

	if (c < 0 || c > 255)
		return (0);
	ch = (unsigned char) c;
	return (ch >= 32 && ch <= 126);
}
