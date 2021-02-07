/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:53:09 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/07 23:05:11 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// unsigned int    texture_color(t_wndw *data, int x, int y, int point)
// {
//     char            *dst;
//     unsigned int    color;
//     dst = data->txtd[point].addr + (y * data->txtd[point].l_length + x * (data->txtd[point].bpp / 8));
//     color = *(unsigned int *)dst;
//     return (color);
// }

int		pixget(t_all *l, int x, int y, int i)
{
	char	*dst;
	int		color;

	dst = l->tx[i].addr + (y * l->tx[i].line_len + x * (l->tx[i].bppixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

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

//change dir to plane
void	move_left(t_all *l)
{
	if (l->map[(int)(l->plr.pos_x + l->plr.dir_y * l->mspeed)][(int)l->plr.pos_y] != '1')
			l->plr.pos_x += l->plr.dir_y * l->mspeed;
	if (l->map[(int)l->plr.pos_x][(int)(l->plr.pos_y - l->plr.dir_x * l->mspeed)] != '1')
			l->plr.pos_y -= l->plr.dir_x * l->mspeed;
}

//change dir to plane
void	move_right(t_all *l)
{
	if (l->map[(int)(l->plr.pos_x - l->plr.dir_y * l->mspeed)][(int)l->plr.pos_y] != '1')
			l->plr.pos_x -= l->plr.dir_y * l->mspeed;
	if (l->map[(int)l->plr.pos_x][(int)(l->plr.pos_y + l->plr.dir_x * l->mspeed)] != '1')
			l->plr.pos_y += l->plr.dir_x * l->mspeed;
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

void	rot_right(t_all *l)
{
	double old_dir_x = l->plr.dir_x;
	l->plr.dir_x = l->plr.dir_x * cos(l->rspeed) - l->plr.dir_y * sin(l->rspeed);
	l->plr.dir_y = old_dir_x * sin(l->rspeed) + l->plr.dir_y * cos(l->rspeed);
	double old_plane_x = l->plane.x;
	l->plane.x = l->plane.x * cos(l->rspeed) - l->plane.y * sin(l->rspeed);
	l->plane.y = old_plane_x * sin(l->rspeed) + l->plane.y * cos(l->rspeed);
}

int 	close_w(void)
{
	exit(0);
}

void	movement(t_all *l)
{
	l->flags.left == 1 ? rot_left(l) : 0;
	l->flags.right == 1 ? rot_right(l) : 0;
	l->flags.forw == 1 ? move_forw(l) : 0;
	l->flags.backw == 1 ? move_back(l) : 0;
	l->flags.movl == 1 ? move_left(l) : 0;
	l->flags.movr == 1 ? move_right(l) : 0;
	l->flags.closew == 1 ? close_w() : 0;
	l->mspeed = l->flags.shift == 1 ? 0.09 : 0.03;
}

int		key_press(int k, t_all *l)
{
	k == 2 ? l->flags.movl = 1 : 0;
	k == 0 ? l->flags.movr = 1 : 0;
	k == 124 ? l->flags.left = 1 : 0;
	k == 123 ? l->flags.right = 1 : 0;	
	k == 13 ? l->flags.forw = 1 : 0;
	k == 1 ? l->flags.backw = 1 : 0;
	k == 257 ? l->flags.shift = 1 : 0;
	k == 53 ? l->flags.closew = 1 : 0;
	return (0);
}

int		key_release(int k, t_all *l)
{
	k == 2 ? l->flags.movl = 0 : 0;
	k == 0 ? l->flags.movr = 0 : 0;
	k == 124 ? l->flags.left = 0 : 0;
	k == 123 ? l->flags.right = 0 : 0;
	k == 13 ? l->flags.forw = 0 : 0;
	k == 1 ? l->flags.backw = 0 : 0;
	k == 257 ? l->flags.shift = 0 : 0;
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

void	open_textures(t_all *l)
{
	l->tx[0].img = mlx_xpm_file_to_image(l->win.mlx, l->txtrs.path_no, &l->w, &l->h);
	l->tx[0].addr = mlx_get_data_addr(l->tx[0].img, &l->tx[0].bppixel, l->tx[0].img, &l->tx[0].endian);

	l->tx[1].img = mlx_xpm_file_to_image(l->win.mlx, l->txtrs.path_we, &l->w, &l->h);
	l->tx[1].addr = mlx_get_data_addr(l->tx[1].img, &l->tx[1].bppixel, l->tx[1].img, &l->tx[1].endian);

	l->tx[2].img = mlx_xpm_file_to_image(l->win.mlx, l->txtrs.path_ea, &l->w, &l->h);
	l->tx[2].addr = mlx_get_data_addr(l->tx[2].img, &l->tx[2].bppixel, l->tx[2].img, &l->tx[2].endian);

	l->tx[3].img = mlx_xpm_file_to_image(l->win.mlx, l->txtrs.path_so, &l->w, &l->h);
	l->tx[3].addr = mlx_get_data_addr(l->tx[3].img, &l->tx[3].bppixel, l->tx[3].img, &l->tx[3].endian);
	// l->tx[4].img = mlx_xpm_file_to_image(l->win.mlx, l->txtrs.path_sp, &l->tx[4].w, &l->tx[4].h);
	// l->tx[4].addr = mlx_get_data_addr(l->tx[4].img, &l->tx[4].bppixel, l->tx[4].img, &l->tx[4].endian);
}

int		cub(t_all *l)
{
	int	x;
	int	i;

	l->win.img = mlx_new_image(l->win.mlx, l->res.x, l->res.y);
	l->win.addr = mlx_get_data_addr(l->win.img, &l->win.bppixel,
	&l->win.line_len, &l->win.endian);
	open_textures(l);
	movement(l);
	x = 0;
	while (x < l->res.x)
	{
		l->cam_x = 2 * x / (double)l->res.x - 1;
		l->ray.dir_x = l->plr.dir_x + l->plane.x * l->cam_x;
		l->ray.dir_y = l->plr.dir_y + l->plane.y * l->cam_x;
		l->map_x = (int)l->plr.pos_x;
		l->map_y = (int)l->plr.pos_y;
		l->delta.dx = fabs(1 / l->ray.dir_x);
		l->delta.dy = fabs(1 / l->ray.dir_y);
		step_side_dist(l);
		hit_side(l);

		l->sd == 0 ?
		(l->p_wall_d = (l->map_x - l->plr.pos_x + (1 - l->step.x) / 2) / l->ray.dir_x) :
		(l->p_wall_d = (l->map_y - l->plr.pos_y + (1 - l->step.y) / 2) / l->ray.dir_y);

		l->l_height = (int)(l->res.y / l->p_wall_d);
		
		l->draw_start = -l->l_height / 2 + l->res.y / 2;
		l->draw_start < 0 ? (l->draw_start = 0) : 0;
		l->draw_end = l->l_height / 2 + l->res.y / 2;
		l->draw_end >= l->res.y ? (l->draw_end = l->res.y - 1) : 0;

		//----------------------------------------------------------------
		l->sd == 0 ?
		(l->wall_x = l->plr.pos_y + l->p_wall_d * l->ray.dir_y) :
		(l->wall_x = l->plr.pos_x + l->p_wall_d * l->ray.dir_x);
		l->wall_x -= floor((l->wall_x));
		l->tex_x = (int)(l->wall_x * (double)l->w);
		l->tex_x = l->w - l->tex_x - 1;
		
		l->zstep = 1.0 * l->h / l->l_height;
		l->tex_pos = (l->draw_start - l->res.y / 2 + l->l_height / 2) * l->zstep;
		//----------------------------------------------------------------

		i = 0;
		while (i < l->res.y)
		{
			if (i < l->draw_start)
				my_mlx_pixel_put(&l->win, x, i, l->color.c);
			else if (i >= l->draw_start && i <= l->draw_end)
			{
				//-------------------------------------------------------------------
				l->tex_y = (int)l->tex_pos & (l->h - 1);
				l->tex_pos += l->zstep;
				if (l->sd == 0)
				{
					if (l->step.x > 0)
						l->rgb = pixget(l, l->tex_x, l->tex_y, 0);
					else
						l->rgb = pixget(l, l->tex_x, l->tex_y, 1);
				}
				else
				{
					if (l->step.y > 0)
						l->rgb = pixget(l, l->tex_x, l->tex_y, 2);
					else
						l->rgb = pixget(l, l->tex_x, l->tex_y, 3);
				}
				my_mlx_pixel_put(&l->win, x, i, l->rgb);
				//-------------------------------------------------------------------
			}
			if (i <= l->res.y && i >= l->draw_end)
				my_mlx_pixel_put(&l->win, x, i, l->color.f);
			i++;
		}
		x++;
	}
	mlx_put_image_to_window(l->win.mlx, l->win.win, l->win.img, 0, 0);
	mlx_string_put(l->win.mlx, l->win.win, l->res.x / 2, l->res.y / 2, 0xFFFFFF, "< >");
	mlx_string_put(l->win.mlx, l->win.win, 10, 5, 0xFFFFFF, "KEUCLIDE");
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