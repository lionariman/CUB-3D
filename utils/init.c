/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:59:32 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/15 19:28:05 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	data_nulling(t_all *f)
{
	f->res.x = 0;
	f->res.y = 0;
	f->txtrs.path_no = NULL;
	f->txtrs.path_we = NULL;
	f->txtrs.path_ea = NULL;
	f->txtrs.path_so = NULL;
	f->txtrs.path_sp = NULL;
	f->color.f = 0;
	f->color.c = 0;
	f->p.x = 0;
	f->p.y = 0;
}

void	init_flags(t_all *f)
{
	f->flags.r_flag = 0;
	f->flags.f_flag = 0;
	f->flags.c_flag = 0;
	f->flags.p_flag = 0;
	f->flags.s_flag = 0;
	f->flags.bmp = 0;
}
