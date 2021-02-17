/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:30:20 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/17 08:39:46 by keuclide         ###   ########.fr       */
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
	int	i;

	i = ft_strlen(arg) - 4;
	if ((fd = open(arg, O_RDONLY)) < 0 || ft_strncmp(&arg[i], ".xpm", 4))
	{
		close(fd);
		return (print_error("xpm file is not valid"));
	}
	return (0);
}

void	check_lim(t_all *l, char **args, int x, int y)
{
	l->res.x = ft_atoi(args[1]);
	l->res.y = ft_atoi(args[2]);
	if (l->res.x > x && l->res.y > y)
	{
		l->res.x = x;
		l->res.y = y;
	}
	else if (l->res.x < 0 || l->res.y < 0)
		print_error("Negative resolution");
	else if (l->res.x < 100 || l->res.y < 100)
	{
		l->res.x = 100;
		l->res.y = 100;
	}
}

int		check_coma(char *line)
{
	int		i;
	int		f;
	int		d;

	f = 0;
	d = 0;
	i = -1;
	while (!ft_isdigit(line[++i]))
		if (line[i] == ',')
			return (-1);
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		(line[i++] == ',') ? (f += 1) : 0;
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		(line[i++] == ',' && f == 1) ? (d += 1) : 0;
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		(line[i++] == ',') ? (f += 1) : 0;
	return ((f == 1 && d == 1) ? 0 : -1);
}
