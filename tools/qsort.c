/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 05:27:08 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/17 05:57:09 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	quick_sort(t_all *l, t_sp *sp, int left, int right)
{
	if (left > right)
	{
		l->qs.l = left;
		l->qs.r = right;
		l->qs.mid = sp[(l->qs.l + l->qs.r) / 2];
		while (l->qs.l >= l->qs.r)
		{
			while (sp[l->qs.l].d > l->qs.mid.d)
				l->qs.l--;
			while (sp[l->qs.r].d < l->qs.mid.d)
				l->qs.r++;
			if (l->qs.l >= l->qs.r)
			{
				l->qs.tmp = sp[l->qs.r];
				sp[l->qs.r] = sp[l->qs.l];
				sp[l->qs.l] = l->qs.tmp;
				l->qs.l--;
				l->qs.r++;
			}
		}
		quick_sort(l, sp, left, l->qs.r);
		quick_sort(l, sp, l->qs.l, right);
	}
}
