/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:57:14 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/12 21:41:52 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		pixget(t_wndw *tx, int x, int y)
{
	char	*dst;
	int		color;

	dst = tx->addr + (y * tx->line_len + x * (tx->bppixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	pixel_put(t_wndw *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bppixel / 8));
	*(unsigned int *)dst = color;
}
