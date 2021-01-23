/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:35:50 by keuclide          #+#    #+#             */
/*   Updated: 2020/12/10 14:48:38 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"



static long long int	pow(long long int e)
{
	long long int	z;

	z = 1;
	while (e--)
		z *= 10;
	return (z);
}

static void				ptnbr(long long int n, long long int z,
int i, int fd)
{
	char m;

	while (i != 0)
	{
		m = (n / (10 * z)) % 10 + '0';
		ft_putchar_fd(m, fd);
		z /= 10;
		i--;
		if (i == 0)
		{
			i = 2;
			z = 10;
			while (i != 0)
			{
				m = (n / (1 * z)) % 10 + '0';
				ft_putchar_fd(m, fd);
				z /= 10;
				i--;
			}
		}
	}
}

static int				size(long long int v)
{
	int	i;

	i = 0;
	while (v / 10 != 0)
	{
		v /= 10;
		i++;
	}
	i -= 1;
	return (i);
}

static void				two(long long int n, int fd)
{
	char			m;
	long long int	z;
	int				i;

	i = 2;
	z = 10;
	while (i != 0)
	{
		m = (n / (1 * z)) % 10 + '0';
		ft_putchar_fd(m, fd);
		z /= 10;
		i--;
	}
}

void					ft_putnbr_fd(long long int v, int fd)
{
	int				i;
	long long int	z;

	if (v < 0)
	{
		v *= -1;
		ft_putchar_fd('-', fd);
	}
	if (v > 99)
	{
		i = size(v);
		z = pow(i);
		ptnbr(v, z, i, fd);
	}
	if (v < 100 && v > 9)
		two(v, fd);
	if (v < 10 && v >= 0)
		ft_putchar_fd((v + '0'), fd);
}