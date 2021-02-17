/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:30:16 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/17 05:57:29 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	trans_sprite(t_all *l, t_sp *sp, int i)
{
	t_sp s;

	s.x = (sp[i].x - l->plr.pos_x) + 0.5;
	s.y = (sp[i].y - l->plr.pos_y) + 0.5;
	l->inv_d = 1.0 / (l->plane.x * l->plr.dir_y - l->plr.dir_x * l->plane.y);
	l->trans_x = l->inv_d * (l->plr.dir_y * s.x - l->plr.dir_x * s.y);
	l->trans_y = l->inv_d * (-l->plane.y * s.x + l->plane.x * s.y);
}

void	lowest_highest_pix(t_all *l)
{
	l->spscr_x = (int)((l->res.x / 2) * (1 + l->trans_x / l->trans_y));
	l->sph = fabs(l->res.y / l->trans_y);
	l->start_y = -l->sph / 2 + l->res.y / 2;
	(l->start_y < 0) ? (l->start_y = 0) : 0;
	l->end_y = l->sph / 2 + l->res.y / 2;
	(l->end_y >= l->res.y) ? (l->end_y = l->res.y - 1) : 0;
	l->spw = fabs(l->res.y / l->trans_y);
	l->start_x = -l->spw / 2 + l->spscr_x;
	(l->start_x < 0) ? (l->start_x = 0) : 0;
	l->end_x = l->spw / 2 + l->spscr_x;
	(l->end_x >= l->res.x) ? (l->end_x = l->res.x - 1) : 0;
}

void	sprite_dye(t_all *l, double *z_buf)
{
	int		j;

	l->st = l->start_x;
	while (l->st < l->end_x)
	{
		l->tex_x = (int)(256 * (l->st - (-l->spw / 2 + l->spscr_x)) *
		l->w / l->spw) / 256;
		if (l->trans_y > 0 && l->st > 0 && l->st < l->res.x &&
		l->trans_y < z_buf[l->st])
		{
			j = l->start_y;
			while (j < l->end_y)
			{
				l->d = j * 256 - l->res.y * 128 + l->sph * 128;
				l->tex_y = ((l->d * l->h) / l->sph) / 256;
				l->rgb = pixget(&l->tx[4], l->tex_x, l->tex_y);
				if ((l->rgb & 0x00FFFFFF) != 0)
					pixel_put(&l->win, l->st, j, l->rgb);
				j++;
			}
		}
		l->st++;
	}
}

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
	int	i;

	i = -1;
	while (++i < l->flags.s_flag)
		sp[i].d = ((l->plr.pos_x - sp[i].x) * (l->plr.pos_x - sp[i].x) +
					(l->plr.pos_y - sp[i].y) * (l->plr.pos_y - sp[i].y));
	quick_sort(l, sp, l->flags.s_flag - 1, 0);
}
