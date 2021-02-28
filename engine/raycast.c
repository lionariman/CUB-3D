/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:47:32 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/16 00:26:14 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ray_pos_dir(t_all *l, int x)
{
	l->cam_x = 2 * x / (double)l->res.x - 1;
	l->ray.dir_x = l->plr.dir_x + l->plane.x * l->cam_x;
	l->ray.dir_y = l->plr.dir_y + l->plane.y * l->cam_x;
	l->map_x = (int)l->plr.pos_x;
	l->map_y = (int)l->plr.pos_y;
	l->delta.dx = fabs(1 / l->ray.dir_x);
	l->delta.dy = fabs(1 / l->ray.dir_y);
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

void	dda_performance(t_all *l)
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

void	wall_building(t_all *l)
{
	l->sd == 0 ?
	(l->p_wall_d = (l->map_x - l->plr.pos_x +
	(1 - l->step.x) / 2) / l->ray.dir_x) :
	(l->p_wall_d = (l->map_y - l->plr.pos_y +
	(1 - l->step.y) / 2) / l->ray.dir_y);
	l->l_height = (int)((l->res.x / l->p_wall_d) * 0.75);
	l->draw_start = -l->l_height / 2 + l->res.y / 2;
	(l->draw_start < 0) ? (l->draw_start = 0) : 0;
	l->draw_end = l->l_height / 2 + l->res.y / 2;
	(l->draw_end >= l->res.y) ? (l->draw_end = l->res.y - 1) : 0;
}
