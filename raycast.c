/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:53:09 by keuclide          #+#    #+#             */
/*   Updated: 2021/01/31 18:27:54 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// int		key_hook(int keycode, t_wndw *win)
// {
// 	if (keycode == 53)
// 		mlx_destroy_window(win->mlx, win->win);
// 	return (0);
// }

// void	my_mlx_pixel_put(t_wndw *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_len + x * (data->bppixel / 8));
// 	*(unsigned int *)dst = color;
// }

// void	scale_map(t_all all, int i, int j)
// {
// 	int x;
// 	int y;

// 	x = (j + 1) * SCALE;
// 	y = (i + 1) * SCALE;
// 	j *= SCALE;
// 	i *= SCALE;
// 	while (i < y)
// 	{
// 		while (j < x)
// 		{
// 			my_mlx_pixel_put(&all.win, j, i, all.color.c);
// 			j++;
// 		}
// 		j -= SCALE;
// 		i++;
// 	}
// }


int		make_cub(t_all *l)
{
	int		x;

	x = 0;
	while (x < l->res.x)
	{
		l->camX = 2 * x / float(->res.x) - 1; // x-coordinate in camera space
		l->ray.dirX = l->plr.dirX + l->plane.x * l->camX;
		l->ray.dirY = l->plr.dirY + l->plane.y * l->camX;

		//which box of the map we're in
		l->map[l->p.x] = int(l->plr.posX);
		l->map[l->p.y] = int(l->plr.posY);

		//length of ray from one x or y-side to next x or y-side
		l->delta.dX = abs(1 / l->ray.dirX);
		l->side.dY = abs(1 / l->ray.dirY);

		
		s++;
	}
	return (0);   
}

int		raycast(t_all *all)
{
	int i;
	int j;

	i = 0;
	all->win.mlx = mlx_init();
	all->win.win = mlx_new_window(all->win.mlx, all->res.x, all->res.y, "Wolfenstein");
	all->win.img = mlx_new_image(all->win.mlx, all->res.x, all->res.y);
	all->win.addr = mlx_get_data_addr(all->win.img, &all->win.bppixel,
									&all->win.line_len, &all->win.endian);
	if (make_cub(all) == -1)
		return (print_error("ERROR!"));
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
	mlx_loop(all->win.mlx);
	return (0);
}