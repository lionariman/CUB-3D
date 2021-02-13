/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 09:42:46 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/13 12:02:06 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rot_left(t_all *l)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = l->plr.dir_x;
	l->plr.dir_x = l->plr.dir_x *
	cos(-l->rspeed) - l->plr.dir_y * sin(-l->rspeed);
	l->plr.dir_y = old_dir_x *
	sin(-l->rspeed) + l->plr.dir_y * cos(-l->rspeed);
	old_plane_x = l->plane.x;
	l->plane.x = l->plane.x *
	cos(-l->rspeed) - l->plane.y * sin(-l->rspeed);
	l->plane.y = old_plane_x *
	sin(-l->rspeed) + l->plane.y * cos(-l->rspeed);
}

void	rot_right(t_all *l)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = l->plr.dir_x;
	l->plr.dir_x = l->plr.dir_x *
	cos(l->rspeed) - l->plr.dir_y * sin(l->rspeed);
	l->plr.dir_y = old_dir_x *
	sin(l->rspeed) + l->plr.dir_y * cos(l->rspeed);
	old_plane_x = l->plane.x;
	l->plane.x = l->plane.x *
	cos(l->rspeed) - l->plane.y * sin(l->rspeed);
	l->plane.y = old_plane_x *
	sin(l->rspeed) + l->plane.y * cos(l->rspeed);
}
