/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:53:09 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/03 05:43:24 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// int		key_hook(int keycode, t_wndw *win)
// {
// 	if (keycode == 53)
// 		mlx_destroy_window(win->mlx, win->win);
// 	return (0);
// }

void	my_mlx_pixel_put(t_wndw *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bppixel / 8));
	*(unsigned int *)dst = color;
}

int		key_press(int key, t_all *l)
{
	mlx_clear_window(l->win.mlx, l->win.win);
	(key == 53) ? (exit(0)) : 0;
	raycast(l);
	ft_putendl_fd("click", 1);
	return (0);
}

// int		key_release(int key, t_all *l)
// {
// }

void	step_side_dist(t_all *l)
{
	if (l->ray.dirX < 0)
	{
		l->step.x = -1;
		l->side.dX = (l->plr.posX - l->mapX) * l->delta.dX;
	}
	else
	{
		l->step.x = 1;
		l->side.dX = (l->mapY + 1.0 - l->plr.posX) * l->delta.dX;
	}
	if (l->ray.dirY < 0)
	{
		l->step.y = -1;
		l->side.dY = (l->plr.posY - l->mapY) * l->delta.dY;
	}
	else
	{
		l->step.y = 1;
		l->side.dY = (l->mapY + 1.0 - l->plr.posY) * l->delta.dY;
	}
}

void	hit_side(t_all *l)
{
	l->hit = 0;
	while (l->hit == 0)
	{
		if (l->side.dX < l->side.dY)
		{
			l->side.dX += l->delta.dX;
			l->mapX += l->step.x;
			l->sd = 0;
		}
		else
		{
			l->side.dY += l->delta.dY;
			l->mapY += l->step.y;
			l->sd = 1;
		}
		(l->map[l->mapY][l->mapX] == '1') ? (l->hit = 1) : 0;
	}
}

void	cub(t_all *l)
{
	int	x;

	x = 0;
	while (x < l->res.x)
	{
		// координата х на плоскости камеры, которую представляет
		// текущая координата х экрана, сделаная таким образом, чтобы
		// правая сторона экрана получила координату 1, центр 0, а левая -1.
		l->camX = 2 * x / (float)l->res.x - 1;


		// Направление луча может быть вычислено как сумма вектора направления
		// и часть вектора плоскости.
		l->ray.dirX = l->plr.dirX + l->plane.x;// * l->camX;
		l->ray.dirY = l->plr.dirY + l->plane.y;// * l->camX;
		
		l->mapX = (int)l->plr.posX;
		l->mapY = (int)l->plr.posY;

		l->delta.dX = fabs(1 / l->ray.dirX);
		l->delta.dY = fabs(1 / l->ray.dirY);

		step_side_dist(l);
		hit_side(l);
		
		(l->sd == 0) ?
		(l->pWallDist = (l->mapX - l->plr.posX + (1 - l->step.x) / 2) / l->ray.dirX) :
		(l->pWallDist = (l->mapY - l->plr.posY + (1 - l->step.y) / 2) / l->ray.dirY);

		l->l_height = (l->res.y / l->pWallDist);

		l->draw_start = -l->l_height / 2 + l->res.y / 2;
		(l->draw_start < 0) ? (l->draw_start = 0) : 0;

		l->draw_end = l->l_height / 2 + l->res.y / 2;
		(l->draw_end >= l->res.y) ? (l->draw_end = l->res.y - 1) : 0;

		while (l->draw_start < l->draw_end)
		{
			my_mlx_pixel_put(&l->win, x, l->draw_start, 0xFFFFFF);
			l->draw_start++;
		}
		x++;
	}
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
	cub(all);
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
	mlx_destroy_image(all->win.mlx, all->win.img);
	mlx_hook(all->win.win, 2, 0, &key_press, all);
	// mlx_hook(all->win.win, 3, 0, &key_release, all);
	// mlx_loop_hook(all->win.mlx, &cub, all);
	mlx_loop(all->win.mlx);
	return (0);
}