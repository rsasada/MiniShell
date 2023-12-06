/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:47:13 by jongykim          #+#    #+#             */
/*   Updated: 2023/05/20 23:13:54 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;
	long	nbr;

	len = count_len (n);
	result = (char *) malloc (sizeof (char) * (len + 1));
	if (result == NULL)
		return (NULL);
	nbr = n;
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	if (nbr == 0)
		result[0] = '0';
	result[len] = '\0';
	len--;
	while (nbr)
	{
		result[len] = nbr % 10 + '0';
		len--;
		nbr /= 10;
	}
	return (result);
}
