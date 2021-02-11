/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 09:43:44 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/11 16:56:17 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	move_forw(t_all *l)
// {
// 	if (l->map[(int)(l->plr.pos_x + l->plr.dir_x * l->mspeed)][(int)l->plr.pos_y] != '1')	
// 			l->plr.pos_x += l->plr.dir_x * l->mspeed;
// 	if (l->map[(int)l->plr.pos_x][(int)(l->plr.pos_y + l->plr.dir_y * l->mspeed)] != '1')	
// 			l->plr.pos_y += l->plr.dir_y * l->mspeed;
// }

// void	move_back(t_all *l)
// {
// 	if (l->map[(int)(l->plr.pos_x - l->plr.dir_x * l->mspeed)][(int)l->plr.pos_y] != '1')	
// 			l->plr.pos_x -= l->plr.dir_x * l->mspeed;
// 	if (l->map[(int)l->plr.pos_x][(int)(l->plr.pos_y - l->plr.dir_y * l->mspeed)] != '1')	
// 			l->plr.pos_y -= l->plr.dir_y * l->mspeed;
// }

void	move_forw(t_all *l)
{
	if (l->map[(int)(l->plr.pos_x - l->plane.y * l->mspeed)][(int)l->plr.pos_y] != '1')	
			l->plr.pos_x -= l->plane.y * l->mspeed;
	if (l->map[(int)l->plr.pos_x][(int)(l->plr.pos_y + l->plane.x * l->mspeed)] != '1')	
			l->plr.pos_y += l->plane.x * l->mspeed;
}

void	move_back(t_all *l)
{
	if (l->map[(int)(l->plr.pos_x + l->plane.y * l->mspeed)][(int)l->plr.pos_y] != '1')	
			l->plr.pos_x += l->plane.y * l->mspeed;
	if (l->map[(int)l->plr.pos_x][(int)(l->plr.pos_y - l->plane.x * l->mspeed)] != '1')	
			l->plr.pos_y -= l->plane.x * l->mspeed;
}

void	move_left(t_all *l)
{
	if (l->map[(int)(l->plr.pos_x + l->plane.x * l->mspeed)][(int)l->plr.pos_y] != '1')
			l->plr.pos_x += l->plane.x * l->mspeed;
	if (l->map[(int)l->plr.pos_x][(int)(l->plr.pos_y + l->plane.y * l->mspeed)] != '1')
			l->plr.pos_y += l->plane.y * l->mspeed;
}

void	move_right(t_all *l)
{
	if (l->map[(int)(l->plr.pos_x - l->plane.x * l->mspeed)][(int)l->plr.pos_y] != '1')
			l->plr.pos_x -= l->plane.x * l->mspeed;
	if (l->map[(int)l->plr.pos_x][(int)(l->plr.pos_y - l->plane.y * l->mspeed)] != '1')
			l->plr.pos_y -= l->plane.y * l->mspeed;
}

int 	close_w(void)
{
	exit(0);
}
