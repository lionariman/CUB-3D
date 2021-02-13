/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:06:02 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/13 10:29:26 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	bmp_info(t_all *l, int i, int fd)
{
	unsigned int	n;
	short			z;

	n = 40;
	write(fd, &n, 4);
	write(fd, &l->res.x, 4);
	write(fd, &l->res.y, 4);
	z = 1;
	write(fd, &z, 2);
	z = 32;
	write(fd, &z, 2);
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
}

void	create_bmp(t_all *l, int fd)
{
	int				size;
	int				i;

	write(fd, "BM", 2);
	size = 54 + (l->res.x * l->res.y * 4);
	write(fd, &size, 4);
	i = 0;
	write(fd, &i, 4);
	i = 54;
	write(fd, &i, 4);
	bmp_info(l, i, fd);
	i = l->res.y;
	while (i > 0)
	{
		i--;
		write(fd, l->win.addr + (i * l->win.line_len),
		l->res.x * (l->win.bppixel / 8));
	}
	close(fd);
	exit(0);
}
