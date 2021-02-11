/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallcasting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:51:44 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/11 12:41:20 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	tex_coordinates(t_all *l)
{
	l->sd == 0 ?
	(l->wall_x = l->plr.pos_y + l->p_wall_d * l->ray.dir_y) :
	(l->wall_x = l->plr.pos_x + l->p_wall_d * l->ray.dir_x);
	l->wall_x -= floor(l->wall_x);
	l->tex_x = (int)(l->wall_x * (double)l->w);
	l->tex_x = l->w - l->tex_x - 1;
	l->zstep = 1.0 * l->h / l->l_height;
	l->tex_pos = (l->draw_start - l->res.y / 2 + l->l_height / 2) * l->zstep;
}

void	wall_dye(t_all *l, int x, int i)
{
	i = 0;
	while (i < l->res.y)
	{
		if (i < l->draw_start)
			pixel_put(&l->win, x, i, l->color.c);
		else if (i > l->draw_start && i < l->draw_end)
		{
			l->tex_y = (int)l->tex_pos & (l->h - 1);
			l->tex_pos += l->zstep;
			if (l->sd == 0)
				(l->step.x > 0) ?
				(l->rgb = pixget(&l->tx[3], l->tex_x, l->tex_y)) :
				(l->rgb = pixget(&l->tx[0], l->tex_x, l->tex_y));
			else
				(l->step.y > 0) ?
				(l->rgb = pixget(&l->tx[2], l->tex_x, l->tex_y)) :
				(l->rgb = pixget(&l->tx[1], l->tex_x, l->tex_y));
			pixel_put(&l->win, x, i, l->rgb);
		}
		else if (i < l->res.y && i > l->draw_end)
			pixel_put(&l->win, x, i, l->color.f);
		i++;
	}
}
