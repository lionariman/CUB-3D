/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:05:53 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/11 15:27:16 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		skiplines(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
		i++;
	return (i - 1);
}

int		skipspaces(char *line)
{
	int i;
	
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}
