/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:53:09 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/20 11:27:19 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_img(t_all *l)
{
	if (!(l->tx[0].img = mlx_xpm_file_to_image(l->win.mlx,
							l->txtrs.path_no, &l->txtrs.w_no, &l->txtrs.h_no)) ||
		!(l->tx[1].img = mlx_xpm_file_to_image(l->win.mlx,
							l->txtrs.path_we, &l->txtrs.w_we, &l->txtrs.h_we)) ||
		!(l->tx[2].img = mlx_xpm_file_to_image(l->win.mlx,
							l->txtrs.path_ea, &l->txtrs.w_ea, &l->txtrs.h_ea)) ||
		!(l->tx[3].img = mlx_xpm_file_to_image(l->win.mlx,
							l->txtrs.path_so, &l->txtrs.w_so, &l->txtrs.h_so)) ||
		!(l->tx[4].img = mlx_xpm_file_to_image(l->win.mlx,
							l->txtrs.path_sp, &l->txtrs.w_sp, &l->txtrs.h_sp)) ||
		!(l->tx[5].img = mlx_xpm_file_to_image(l->win.mlx,
							l->txtrs.path_fl, &l->txtrs.w_fl, &l->txtrs.h_fl)))
		print_error("xmp file is broken");
}

void	get_addr(t_all *l)
{
	l->tx[0].addr = mlx_get_data_addr(l->tx[0].img, &l->tx[0].bppixel,
								&l->tx[0].line_len, &l->tx[0].endian);
	l->tx[1].addr = mlx_get_data_addr(l->tx[1].img, &l->tx[1].bppixel,
								&l->tx[1].line_len, &l->tx[1].endian);
	l->tx[2].addr = mlx_get_data_addr(l->tx[2].img, &l->tx[2].bppixel,
								&l->tx[2].line_len, &l->tx[2].endian);
	l->tx[3].addr = mlx_get_data_addr(l->tx[3].img, &l->tx[3].bppixel,
								&l->tx[3].line_len, &l->tx[3].endian);
	l->tx[4].addr = mlx_get_data_addr(l->tx[4].img, &l->tx[4].bppixel,
								&l->tx[4].line_len, &l->tx[4].endian);
	l->tx[5].addr = mlx_get_data_addr(l->tx[5].img, &l->tx[5].bppixel,
								&l->tx[5].line_len, &l->tx[5].endian);
}

void	wall_sprite_cast(t_all *l, t_sp *sp, double *z_buf)
{
	int x;
	int y;
	int i;

	y = l->res.y / 2 + 1;
	i = l->flags.s_flag;

//----------------------------------------------------------------------

	while (++y < l->res.y)
	{
		l->rdirx0 = l->plr.dir_x - l->plane.x;
		l->rdiry0 = l->plr.dir_y - l->plane.y;
		l->rdirx1 = l->plr.dir_x + l->plane.x;
		l->rdirx1 = l->plr.dir_y + l->plane.y;
		l->pp = y - l->res.y / 2;
		l->pos_z = 0.5 *l->res.y;
		l->row_dist = l->pos_z / l->pp;
		l->f_st_x = l->row_dist * (l->rdirx1 - l->rdirx0) / l->res.x;
		l->f_st_y = l->row_dist * (l->rdiry1 - l->rdiry0) / l->res.x;
		l->f_x = l->plr.pos_x + l->row_dist * l->rdirx0;
		l->f_y = l->plr.pos_y + l->row_dist * l->rdiry0;

		x = -1;
		while (++x < l->res.x)
		{
			l->cellx = (int)(l->f_x);
			l->celly = (int)(l->f_y);
			l->txx = (int)(l->txtrs.w_fl * (l->f_x - l->cellx)) & (l->txtrs.w_fl - 1);
			l->tyy = (int)(l->txtrs.h_fl * (l->f_y - l->celly)) & (l->txtrs.h_fl - 1);
			l->f_x += l->f_st_x;
			l->f_y += l->f_st_y;
			l->rgb = pixget(&l->tx[5], l->txx, l->tyy);
			pixel_put(&l->win, x, l->res.y - 1 - y, l->rgb);
		}
	}

	x = -1;

//----------------------------------------------------------------------

	while (++x < l->res.x)
	{
		ray_pos_dir(l, x);
		step_side_dist(l);
		dda_performance(l);
		wall_building(l);
		tex_coordinates(l);
		wall_dye(l, x, i);
		z_buf[x] = l->p_wall_d;
	}
	find_sprites(l, sp);
	sort_sprites(l, sp);
	while (i >= 0)
	{
		trans_sprite(l, sp, i);
		lowest_highest_pix(l);
		sprite_dye(l, z_buf);
		i--;
	}
}

int		raycast(t_all *l)
{
	t_sp	sp[l->flags.s_flag];
	double	z_buf[l->res.x];

	l->win.img = mlx_new_image(l->win.mlx, l->res.x, l->res.y);
	l->win.addr = mlx_get_data_addr(l->win.img, &l->win.bppixel,
	&l->win.line_len, &l->win.endian);
	movement(l);
	wall_sprite_cast(l, sp, z_buf);
	if (l->flags.bmp == 0)
	{
		mlx_put_image_to_window(l->win.mlx, l->win.win, l->win.img, 0, 0);
		mlx_string_put(l->win.mlx, l->win.win, l->res.x / 2, l->res.y / 2,
		0xFFFFFF, "< >");
		mlx_destroy_image(l->win.mlx, l->win.img);
	}
	return (0);
}

int		cub(t_all *l)
{
	l->mspeed = 0.1;
	l->rspeed = 0.08;
	l->win.win = mlx_new_window(l->win.mlx, l->res.x, l->res.y, "wolfencub");
	get_img(l);
	get_addr(l);
	mlx_hook(l->win.win, 2, 0, key_press, l);
	mlx_hook(l->win.win, 3, 0, key_release, l);
	mlx_hook(l->win.win, 17, 0, close_w, l);
	mlx_loop_hook(l->win.mlx, raycast, l);
	mlx_loop(l->win.mlx);
	return (0);
}
