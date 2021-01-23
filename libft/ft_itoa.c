/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:49:48 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/10 00:11:20 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*from_int_to_char(char *mem, int i, long m, int sign)
{
	mem[i] = '\0';
	i--;
	if (m == 0)
		mem[0] = '0';
	while (m > 0)
	{
		mem[i] = m % 10 + '0';
		m /= 10;
		i--;
	}
	if (sign < 0)
		mem[0] = '-';
	return (mem);
}

static int	size(int i, long m)
{
	long n;

	n = m;
	while (n / 10 != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*mem;
	int		i;
	int		sign;
	long	m;

	m = (long)n;
	i = 1;
	sign = 1;
	if (m < 0)
	{
		m = -m;
		sign = -1;
		i++;
	}
	i = size(i, m);
	if ((mem = (char*)malloc((sizeof(char) * (i + 1)))) == NULL)
		return (NULL);
	return (from_int_to_char(mem, i, m, sign));
}
