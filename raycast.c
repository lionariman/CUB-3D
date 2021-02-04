/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:53:09 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/04 06:32:14 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_wndw *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bppixel / 8));
	*(unsigned int *)dst = color;
}

void	move_forw(t_all *l)
{
	if (l->map[(int)(l->plr.posX + l->plr.dirX * l->mspeed)][(int)l->plr.posY] != '1')
		l->plr.posX += l->plr.dirX * l->mspeed;
	if (l->map[(int)l->plr.posX][(int)(l->plr.posY + l->plr.dirY * l->mspeed)] != '1')
		l->plr.posY += l->plr.dirY * l->mspeed;
}
void	move_back(t_all *l)
{
	if (l->map[(int)(l->plr.posX - l->plr.dirX * l->mspeed)][(int)l->plr.posY] != '1')
		l->plr.posX -= l->plr.dirX * l->mspeed;
	if (l->map[(int)l->plr.posX][(int)(l->plr.posY - l->plr.dirY * l->mspeed)] != '1')
		l->plr.posY -= l->plr.dirY * l->mspeed;
}
void	rot_left(t_all *l)
{
	float old_dirX = l->plr.dirX;
	float old_planeX = l->plane.x;
	l->plr.dirX = l->plr.dirX * cos(l->rspeed) - l->plr.dirY * sin(l->rspeed);
	l->plr.dirY = old_dirX * sin(l->rspeed) + l->plr.dirY * cos(l->rspeed);
	l->plane.x = l->plane.x * cos(l->rspeed) - l->plane.y * sin(l->rspeed);
	l->plane.y = old_planeX * sin(l->rspeed) + l->plane.y * cos(l->rspeed);
}
void	rot_right(t_all *l)
{
	float old_dirX = l->plr.dirX;
	float old_planeX = l->plane.x;
	l->plr.dirX = l->plr.dirX * cos(-l->rspeed) - l->plr.dirY * sin(-l->rspeed);
	l->plr.dirY = old_dirX * sin(-l->rspeed) + l->plr.dirY * cos(-l->rspeed);
	l->plane.x = l->plane.x * cos(-l->rspeed) - l->plane.y * sin(-l->rspeed);
	l->plane.y = old_planeX * sin(-l->rspeed) + l->plane.y * cos(-l->rspeed);
}

int 	close_w(void)
{
	printf("you have closed the game\n");
	exit(0);
	return (0);
}

int		movement(t_all *l)
{
	(l->flags.left == 1) ? rot_left(l) : 0;
	(l->flags.right == 1) ? rot_right(l) : 0;
	(l->flags.forw == 1) ? move_forw(l) : 0;
	(l->flags.backw == 1) ? move_back(l) : 0;
	(l->flags.closew == 1) ? close_w() : 0;
	return (0);
}

int		key_press(int k, t_all *l)
{
	(k == 0) ? l->flags.left = 1 : 0;
	(k == 2) ? l->flags.right = 1 : 0;
	(k == 13) ? l->flags.forw = 1 : 0;
	(k == 1) ? l->flags.backw = 1 : 0;
	(k == 53) ? l->flags.closew = 1 : 0;
	return (0);
}

int		key_release(int k, t_all *l)
{
	(k == 0) ? l->flags.left = 0 : 0;
	(k == 2) ? l->flags.right = 0 : 0;
	(k == 13) ? l->flags.forw = 0 : 0;
	(k == 1) ? l->flags.backw = 0 : 0;
	return (0);
}

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

int		cub(t_all *l)
{
	int	x;

	l->win.img = mlx_new_image(l->win.mlx, l->res.x, l->res.y);
	l->win.addr = mlx_get_data_addr(l->win.img, &l->win.bppixel,
	&l->win.line_len, &l->win.endian);
	x = 0;
	movement(l);
	while (x < l->res.x)
	{
		// координата х на плоскости камеры, которую представляет
		// текущая координата х экрана, сделаная таким образом, чтобы
		// правая сторона экрана получила координату 1, центр 0, а левая -1.
		l->camX = 2 * x / (float)l->res.x - 1;


		// Направление луча может быть вычислено как сумма вектора направления
		// и часть вектора плоскости.
		l->ray.dirX = l->plr.dirX + l->plane.x * l->camX;
		l->ray.dirY = l->plr.dirY + l->plane.y * l->camX;
		
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
			my_mlx_pixel_put(&l->win, x, l->draw_start, 0xFF0000);
			l->draw_start++;
		}
		x++;
	}
	mlx_put_image_to_window(l->win.mlx, l->win.win, l->win.img, 0, 0);
	mlx_destroy_image(l->win.mlx, l->win.img);
	return (0);
}

int		raycast(t_all *l)
{
	l->mspeed = 0.1;
	l->rspeed = 0.1;
	l->win.mlx = mlx_init();
	l->win.win = mlx_new_window(l->win.mlx, l->res.x, l->res.y, "Wolfenstein");
	mlx_hook(l->win.win, 2, 0, key_press, l);
	mlx_hook(l->win.win, 3, 0, key_release, l);
	mlx_hook(l->win.win, 17, 0, close_w, l);
	mlx_loop_hook(l->win.mlx, cub, l);
	mlx_loop(l->win.mlx);
	return (0);
}