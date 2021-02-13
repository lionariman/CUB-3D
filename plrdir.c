/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plrdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:57:39 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/13 11:45:52 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	north_west(t_all *all, int i, int j)
{
	if (all->map[i][j] == 'N')
	{
		all->plr.dir_x = -1;
		all->plr.dir_y = 0;
		all->plane.x = 0;
		all->plane.y = 0.70;
	}
	else if (all->map[i][j] == 'W')
	{
		all->plr.dir_x = 0;
		all->plr.dir_y = -1;
		all->plane.x = -0.70;
		all->plane.y = 0;
	}
}

void	south_east(t_all *all, int i, int j)
{
	if (all->map[i][j] == 'E')
	{
		all->plr.dir_x = 0;
		all->plr.dir_y = 1;
		all->plane.x = 0.70;
		all->plane.y = 0;
	}
	else if (all->map[i][j] == 'S')
	{
		all->plr.dir_x = 1;
		all->plr.dir_y = 0;
		all->plane.x = 0;
		all->plane.y = -0.70;
	}
}

void	player_pos(t_all *all, int i, int j)
{
	all->plr.pos_x = i + 0.5;
	all->plr.pos_y = j + 0.5;
	north_west(all, i, j);
	south_east(all, i, j);
}
