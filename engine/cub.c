/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:53:09 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/20 09:57:26 by keuclide         ###   ########.fr       */
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
							l->txtrs.path_sp, &l->txtrs.w_sp, &l->txtrs.h_sp)))
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
}

void	wall_sprite_cast(t_all *l, t_sp *sp, double *z_buf)
{
	int x;
	int i;

	x = 0;
	i = l->flags.s_flag;
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
	t_sp	*sp;
	double	z_buf[l->res.x];

	if (!(sp = malloc(sizeof(t_sp) * (l->flags.s_flag + 1))))
		print_error("cannot allocate memory");
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
	free(sp);
	return (0);
}

int		cub(t_all *l)
{
	l->mspeed = 0.1;
	l->rspeed = 0.08;
	l->win.win = mlx_new_window(l->win.mlx, l->res.x, l->res.y, "wolfencub");
	get_img(l);
	get_addr(l);
	// printf("wno---%d---\n", l->txtrs.w_no);
	// printf("wwe---%d---\n", l->txtrs.w_we);
	// printf("wea---%d---\n", l->txtrs.w_ea);
	// printf("wso---%d---\n", l->txtrs.w_so);
	// printf("hno---%d---\n", l->txtrs.h_no);
	// printf("hwe---%d---\n", l->txtrs.h_we);
	// printf("hea---%d---\n", l->txtrs.h_ea);
	// printf("hso---%d---\n", l->txtrs.h_so);
	mlx_hook(l->win.win, 2, 0, key_press, l);
	mlx_hook(l->win.win, 3, 0, key_release, l);
	mlx_hook(l->win.win, 17, 0, close_w, l);
	mlx_loop_hook(l->win.mlx, raycast, l);
	mlx_loop(l->win.mlx);

	return (0);
}
