/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:53:09 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/11 12:10:15 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		pixget(t_wndw *tx, int x, int y)
{
	char	*dst;
	int		color;

	dst = tx->addr + (y * tx->line_len + x * (tx->bppixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	my_mlx_pixel_put(t_wndw *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bppixel / 8));
	*(unsigned int *)dst = color;
}

void	open_textures(t_all *l)
{
	l->tx[0].img = mlx_xpm_file_to_image(l->win.mlx, l->txtrs.path_no, &l->w, &l->h);
	l->tx[0].addr = mlx_get_data_addr(l->tx[0].img, &l->tx[0].bppixel, &l->tx[0].line_len, &l->tx[0].endian);
	l->tx[1].img = mlx_xpm_file_to_image(l->win.mlx, l->txtrs.path_we, &l->w, &l->h);
	l->tx[1].addr = mlx_get_data_addr(l->tx[1].img, &l->tx[1].bppixel, &l->tx[1].line_len, &l->tx[1].endian);
	l->tx[2].img = mlx_xpm_file_to_image(l->win.mlx, l->txtrs.path_ea, &l->w, &l->h);
	l->tx[2].addr = mlx_get_data_addr(l->tx[2].img, &l->tx[2].bppixel, &l->tx[2].line_len, &l->tx[2].endian);
	l->tx[3].img = mlx_xpm_file_to_image(l->win.mlx, l->txtrs.path_so, &l->w, &l->h);
	l->tx[3].addr = mlx_get_data_addr(l->tx[3].img, &l->tx[3].bppixel, &l->tx[3].line_len, &l->tx[3].endian);
	l->tx[4].img = mlx_xpm_file_to_image(l->win.mlx, l->txtrs.path_sp, &l->w, &l->h);
	l->tx[4].addr = mlx_get_data_addr(l->tx[4].img, &l->tx[4].bppixel, &l->tx[4].line_len, &l->tx[4].endian);
}

//--------------------------------------------------------------------------------

void	find_sprites(t_all *l, t_sp *sp)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	n = 0;
	while (l->map[i])
	{
		j = 0;
		while (l->map[i][j])
		{
			if (l->map[i][j] == '2')
			{
				sp[n].x = i;
				sp[n].y = j;
				n++;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprites(t_all *l, t_sp *sp)
{
	int		i;
	t_sp	tmp;
	
	i = -1;
	while (++i < l->flags.s_flag)
		sp[i].d = ((l->plr.pos_x - sp[i].x) * (l->plr.pos_x - sp[i].x) +
					(l->plr.pos_y - sp[i].y) * (l->plr.pos_y - sp[i].y));
	i = 0;
	while (i < l->flags.s_flag - 1)
	{
		if (sp[i].d < sp[i + 1].d)
		{
			tmp = sp[i];
			sp[i] = sp[i + 1];
			sp[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

void	sprite_dye(t_all *l, double *z_buf)
{
	int		j;
	
	l->st = l->start_x;
	while (l->st < l->end_x)
	{
		l->tex_x = (int)(256 * (l->st - (-l->spw / 2 + l->spscr_x)) * l->w / l->spw) / 256;
		if (l->trans_y > 0 && l->st > 0 && l->st < l->res.x && l->trans_y < z_buf[l->st])
		{
			j = l->start_y;
			while (j < l->end_y)
			{
				l->d = j * 256 - l->res.y * 128 + l->sph * 128;
				l->tex_y = ((l->d * l->h) / l->sph) / 256;
				l->rgb = pixget(&l->tx[4], l->tex_x, l->tex_y);
				if ((l->rgb & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&l->win, l->st, j, l->rgb);
				j++;
			}
		}
		l->st++;
	}
}

//--------------------------------------------------------------------------------

int		raycast(t_all *l)
{
	int		x;
	int		i;
	t_sp	tmp;
	t_sp	sp[l->flags.s_flag];
	double	z_buf[l->res.x];

	l->win.img = mlx_new_image(l->win.mlx, l->res.x, l->res.y);
	l->win.addr = mlx_get_data_addr(l->win.img, &l->win.bppixel,
	&l->win.line_len, &l->win.endian);
	open_textures(l);
	movement(l);
	x = 0;
	while (x < l->res.x)
	{
		ray_pos_dir(l, x);
		step_side_dist(l);
		dda_performance(l);
		wall_building(l);
		tex_coordinates(l);
		wall_dye(l, x, i);
		z_buf[x] = l->p_wall_d;
		x++;
	}
	//---------------------------------------------sprites----------------------------------------------------
	find_sprites(l, sp);
	sort_sprites(l, sp);

	i = 0;
	while (i < l->flags.s_flag) //!
	{
		t_sp s;

		//sprite position
		s.x = sp[i].x - l->plr.pos_x;
		s.y = sp[i].y - l->plr.pos_y;
		
		l->inv_d = 1.0 / (l->plane.x * l->plr.dir_y - l->plr.dir_x * l->plane.y);

		l->trans_x = l->inv_d * (l->plr.dir_y * s.x - l->plr.dir_x * s.y);
		l->trans_y = l->inv_d * (-l->plane.y * s.x + l->plane.x * s.y);
		
		l->spscr_x = (int)((l->res.x / 2) * (1 + l->trans_x / l->trans_y));
		
		//height of the sprite (used abs before)
		l->sph = fabs(l->res.y / l->trans_y);

		//lowest and highest pixel to fill in current stripe
		l->start_y = -l->sph / 2 + l->res.y / 2;
		(l->start_y < 0) ? (l->start_y = 0) : 0;
		l->end_y = l->sph / 2 + l->res.y / 2;
		(l->end_y >= l->res.y) ? (l->end_y = l->res.y - 1) : 0;

		//width of the sprite (used abs before)
		l->spw = fabs(l->res.y / l->trans_y);

		l->start_x = -l->spw / 2 + l->spscr_x;
		(l->start_x < 0) ? (l->start_x = 0) : 0;
		l->end_x = l->spw / 2 + l->spscr_x;
		(l->end_x >= l->res.x) ? (l->end_x = l->res.x - 1) : 0;.

		sprite_dye(l, z_buf);
		i++;
	}
	//---------------------------------------------sprites----------------------------------------------------

	mlx_put_image_to_window(l->win.mlx, l->win.win, l->win.img, 0, 0);
	mlx_string_put(l->win.mlx, l->win.win, l->res.x / 2, l->res.y / 2, 0xF50000, "< >");
	mlx_string_put(l->win.mlx, l->win.win, 10, 5, 0xFC2C9B, "KEUCLIDE");
	mlx_destroy_image(l->win.mlx, l->win.img);
	return (0);
}

int		cub(t_all *l)
{
	l->mspeed = 0.05;
	l->rspeed = 0.05;
	l->win.mlx = mlx_init();
	l->win.win = mlx_new_window(l->win.mlx, l->res.x, l->res.y, "cybercub");
	mlx_hook(l->win.win, 2, 0, key_press, l);
	mlx_hook(l->win.win, 3, 0, key_release, l);
	mlx_hook(l->win.win, 17, 0, close_w, l);
	mlx_loop_hook(l->win.mlx, raycast, l);
	mlx_loop(l->win.mlx);
	return (0);
}