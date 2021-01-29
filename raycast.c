/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:53:09 by keuclide          #+#    #+#             */
/*   Updated: 2021/01/29 15:59:22 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	my_mlx_pixel_put(t_wndw *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_len + x * (data->bppixel / 8));
// 	*(unsigned int *)dst = color;
// }

// int		key_hook(int keycode, t_wndw *win)
// {
// 	if (keycode == 53)
// 		mlx_destroy_window(win->mlx, win->win);
// 	return (0);
// }

// void	scale_map(t_all all)
// {
// 	t_point end;

// 	end.x = (all.point.x + 1) * SCALE;
// 	end.y = (all.point.y + 1) * SCALE;
// 	all.point.x *= SCALE;
// 	all.point.y *= SCALE;
// 	while (all.point.y < end.y)
// 	{
// 		while (all.point.x < end.x)
// 		{
// 			mlx_pixel_put(all.win.mlx, all.win.win, all.point.x, all.point.y, 0x0F0FFF);
// 			all.point.x++;
// 		}
// 		all.point.x -= SCALE;
// 		all.point.y++;
// 	}
// }

// void	draw_map(t_all *all)
// {
// 	all->win.mlx = mlx_init();
// 	all->win.win = mlx_new_window(all->win.mlx, all->res.x, all->res.y, "Wolfenstein");

// 	all->point.y = 0;
// 	while (all->map[all->point.y])
// 	{
// 		all->point.x = 0;
// 		while (all->map[all->point.y][all->point.x])
// 		{
// 			if (all->map[all->point.y][all->point.x] == '1')
// 				scale_map(*all);
// 			all->point.x++;
// 		}
// 		all->point.y++;
// 	}
// 	mlx_loop(all->win.mlx);
// }

int		raycast(t_all *all)
{
	int i;
	int j;

	i = 0;
	all->win.mlx = mlx_init();
	all->win.win = mlx_new_window(all->win.mlx, all->res.x, all->res.y, "Wolfenstein");
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				mlx_pixel_put(all->win.mlx, all->win.win, j, i, all->color.f);
			j++;
		}
		i++;
	}
	mlx_loop(all->win.mlx);
	return (0);
}