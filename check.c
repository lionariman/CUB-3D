/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:30:20 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/11 16:02:00 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_flag(t_all *f)
{
	if (f->flags.r_flag == 1 && f->flags.f_flag == 1 && f->flags.c_flag == 1)
		return (0);
	return (-1);
}

int		check_arg(char *s, char c)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (0);
	return (-1);
}

int		check_file(char *arg)
{
	int fd;

	if ((fd = open(arg, O_RDONLY)) < 0)
	{
		close(fd);
		return (print_error("error: xpm file is not valid"));
	}
	return (0);
}

// int		check_coma(char *line)
// {
// 	int n;

// 	n = 0;
// 	while (*line++)
// 		if (*line == ',')
// 			n++;
// 	return ((n != 2) ? -1 : 0);
// }
