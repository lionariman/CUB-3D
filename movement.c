/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 09:45:49 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/13 11:45:10 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	movement(t_all *l)
{
	l->flags.left == 1 ? rot_left(l) : 0;
	l->flags.right == 1 ? rot_right(l) : 0;
	l->flags.forw == 1 ? move_forw(l) : 0;
	l->flags.backw == 1 ? move_back(l) : 0;
	l->flags.movl == 1 ? move_left(l) : 0;
	l->flags.movr == 1 ? move_right(l) : 0;
	l->flags.closew == 1 ? close_w() : 0;
	l->mspeed = l->flags.shift == 1 ? 0.12 : 0.05;
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
