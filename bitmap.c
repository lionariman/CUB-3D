/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:06:02 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/12 23:52:59 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	create_bmp(t_all *l, int fd)
{
	int				size;
	int				i;
	unsigned int	n;
	short			z;

	write(fd, "BM", 2);
	size = 54 + (l->res.x * l->res.y * 4);
	write(fd, &size, 4);
	i = 0;
	write(fd, &i, 4);
	i = 54;
	write(fd, &i, 4);
	n = 40;
	write(fd, &n, 4);
	write(fd, &l->res.x, 4);
	write(fd, &l->res.y, 4);
	z = 1;
	write(fd, &z, 2);
	z = 32;
	write(fd, &z, 2);
	// i = 65568;
	// write(fd, &i, 4);
	n = 0;
	write(fd, &n, 4);
	n = l->res.x * l->res.y;
	write(fd, &n, 4);
	i = 0;
	write(fd, &i, 4);
	i = 0;
	write(fd, &i, 4);
	n = 0;
	write(fd, &n, 4);
	write(fd, &n, 4);
	i = l->res.y;
	while (i > 0)
	{
		i--;
		write(fd, l->win.addr + (i * l->win.line_len), l->res.x * (l->win.bppixel / 8));
	}
}
