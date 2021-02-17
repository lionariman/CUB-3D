/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sputils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 11:56:18 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/13 12:03:00 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_l(t_spl *l)
{
	l->f = 0;
	l->j = 0;
}

char	**freesher(char **mem)
{
	int i;

	i = 0;
	while (mem[i])
	{
		free(mem[i]);
		i++;
	}
	free(mem);
	return (NULL);
}

int		isset(char *s, char c)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}
