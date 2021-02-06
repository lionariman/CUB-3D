/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:53:09 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/06 19:22:51 by keuclide         ###   ########.fr       */
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
	if (l->map[(int)(l->plr.pos_x + l->plr.dir_x * l->mspeed)][(int)l->plr.pos_y] != '1')
			l->plr.pos_x += l->plr.dir_x * l->mspeed;
	if (l->map[(int)l->plr.pos_x][(int)(l->plr.pos_y + l->plr.dir_y * l->mspeed)] != '1')
			l->plr.pos_y += l->plr.dir_y * l->mspeed;
}
void	move_back(t_all *l)
{
	if (l->map[(int)(l->plr.pos_x - l->plr.dir_x * l->mspeed)][(int)l->plr.pos_y] != '1')
			l->plr.pos_x -= l->plr.dir_x * l->mspeed;
	if (l->map[(int)l->plr.pos_x][(int)(l->plr.pos_y - l->plr.dir_y * l->mspeed)] != '1')
			l->plr.pos_y -= l->plr.dir_y * l->mspeed;
}

void	rot_right(t_all *l)
{
	double old_dir_x = l->plr.dir_x;
	l->plr.dir_x = l->plr.dir_x * cos(l->rspeed) - l->plr.dir_y * sin(l->rspeed);
	l->plr.dir_y = old_dir_x * sin(l->rspeed) + l->plr.dir_y * cos(l->rspeed);
	double old_plane_x = l->plane.x;
	l->plane.x = l->plane.x * cos(l->rspeed) - l->plane.y * sin(l->rspeed);
	l->plane.y = old_plane_x * sin(l->rspeed) + l->plane.y * cos(l->rspeed);
}

void	rot_left(t_all *l)
{
	double old_dir_x = l->plr.dir_x;
	l->plr.dir_x = l->plr.dir_x * cos(-l->rspeed) - l->plr.dir_y * sin(-l->rspeed);
	l->plr.dir_y = old_dir_x * sin(-l->rspeed) + l->plr.dir_y * cos(-l->rspeed);
	double old_plane_x = l->plane.x;
	l->plane.x = l->plane.x * cos(-l->rspeed) - l->plane.y * sin(-l->rspeed);
	l->plane.y = old_plane_x * sin(-l->rspeed) + l->plane.y * cos(-l->rspeed);
}

int 	close_w(void)
{
	exit(0);
}

int		movement(t_all *l)
{
	l->flags.left == 1 ? rot_left(l) : 0;
	l->flags.right == 1 ? rot_right(l) : 0;
	l->flags.forw == 1 ? move_forw(l) : 0;
	l->flags.backw == 1 ? move_back(l) : 0;
	l->flags.closew == 1 ? close_w() : 0;
	return (0);
}

int		key_press(int k, t_all *l)
{
	k == 2 ? l->flags.left = 1 : 0;
	k == 0 ? l->flags.right = 1 : 0;
	k == 13 ? l->flags.forw = 1 : 0;
	k == 1 ? l->flags.backw = 1 : 0;
	k == 53 ? l->flags.closew = 1 : 0;
	return (0);
}

int		key_release(int k, t_all *l)
{
	k == 2 ? l->flags.left = 0 : 0;
	k == 0 ? l->flags.right = 0 : 0;
	k == 13 ? l->flags.forw = 0 : 0;
	k == 1 ? l->flags.backw = 0 : 0;
	return (0);
}

void	step_side_dist(t_all *l)
{
	if (l->ray.dir_x < 0)
	{
		l->step.x = -1;
		l->side.dx = (l->plr.pos_x - l->map_x) * l->delta.dx;
	}
	else
	{
		l->step.x = 1;
		l->side.dx = (l->map_x + 1 - l->plr.pos_x) * l->delta.dx;
	}
	if (l->ray.dir_y < 0)
	{
		l->step.y = -1;
		l->side.dy = (l->plr.pos_y - l->map_y) * l->delta.dy;
	}
	else
	{
		l->step.y = 1;
		l->side.dy = (l->map_y + 1 - l->plr.pos_y) * l->delta.dy;
	}
}

void	hit_side(t_all *l)
{
	l->hit = 0;
	while (l->hit == 0)
	{
		if (l->side.dx < l->side.dy)
		{
			l->side.dx += l->delta.dx;
			l->map_x += l->step.x;
			l->sd = 0;
		}
		else
		{
			l->side.dy += l->delta.dy;
			l->map_y += l->step.y;
			l->sd = 1;
		}
		(l->map[l->map_x][l->map_y] == '1') ? (l->hit = 1) : 0;
	}
}

int		cub(t_all *l)
{
	int	x;
	int	i;
	int	rgb;

	l->win.img = mlx_new_image(l->win.mlx, l->res.x, l->res.y);
	l->win.addr = mlx_get_data_addr(l->win.img, &l->win.bppixel,
	&l->win.line_len, &l->win.endian);
	movement(l);
	x = 0;
	while (x < l->res.x)
	{
		l->cam_x = 2 * x / (double)l->res.x - 1;
		l->ray.dir_x = l->plr.dir_x + l->plane.x * l->cam_x;
		l->ray.dir_y = l->plr.dir_y + l->plane.y * l->cam_x;

		l->map_x = (int)l->plr.pos_x;
		l->map_y = (int)l->plr.pos_y;

		//side dis - length of ray from current pos to next x or y-side
		//delta dist - length of ray from one x or y-side to next
		//step - what direction to step in x or y-dir (either +1 or -1)
		l->delta.dx = fabs(1 / l->ray.dir_x);
		l->delta.dy = fabs(1 / l->ray.dir_y);

		step_side_dist(l);
		hit_side(l);
		if (l->sd == 0)
			(l->step.x > 0) ? (rgb = 0x15A49F) : (rgb = 0x721C1C);
		else
			(l->step.y > 0) ? (rgb = 0x0C807B) : (rgb = 0xAC6F13);
		if (l->sd == 0)
			l->p_wall_d = (l->map_x - l->plr.pos_x + (1 - l->step.x) / 2) / l->ray.dir_x;
		else
			l->p_wall_d = (l->map_y - l->plr.pos_y + (1 - l->step.y) / 2) / l->ray.dir_y;
		l->l_height = (int)(l->res.y / l->p_wall_d);

		l->draw_start = -l->l_height / 2 + l->res.y / 2;
		if (l->draw_start < 0)
			l->draw_start = 0;
			
		l->draw_end = l->l_height / 2 + l->res.y / 2;
		if (l->draw_end >= l->res.y)
			l->draw_end = l->res.y - 1;
		i = 0;
		while (i <= l->res.y)
		{
			if (i < l->draw_start)
				my_mlx_pixel_put(&l->win, x, i, l->color.c);
			else if (i >= l->draw_start && i <= l->draw_end)
				my_mlx_pixel_put(&l->win, x, i, rgb);
			if (i <= l->res.y && i >= l->draw_end)
				my_mlx_pixel_put(&l->win, x, i, l->color.f);
			i++;
		}
		x++;
	}
	mlx_put_image_to_window(l->win.mlx, l->win.win, l->win.img, 0, 0);
	mlx_string_put(l->win.mlx, l->win.win, 10, 5, 0xFFFFFF, "keuclide");
	mlx_string_put(l->win.mlx, l->win.win, l->res.x / 2, l->res.y / 2, 0xFFFFFF, "< >");
	mlx_destroy_image(l->win.mlx, l->win.img);
	return (0);
}

int		raycast(t_all *l)
{
	l->mspeed = 0.03;
	l->rspeed = 0.02;
	l->win.mlx = mlx_init();
	l->win.win = mlx_new_window(l->win.mlx, l->res.x, l->res.y, "Wolfenstein");
	mlx_hook(l->win.win, 2, 0, key_press, l);
	mlx_hook(l->win.win, 3, 0, key_release, l);
	mlx_hook(l->win.win, 17, 0, close_w, l);
	mlx_loop_hook(l->win.mlx, cub, l);
	mlx_loop(l->win.mlx);
	return (0);
}