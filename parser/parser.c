/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:28:34 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/17 14:58:23 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		parse_res(char *line, t_all *l)
{
	char	**args;
	int		x;
	int		y;

	mlx_get_screen_size(l->win.mlx, &x, &y);
	args = ft_split(line, ' ');
	if (numw(args) != 3)
	{
		free_maker(args);
		print_error("wrong number of arguments");
	}
	l->flags.r_flag = 1;
	if (digs(args[1]) == -1 || digs(args[2]) == -1)
		print_error("wrong resolution");
	else if (ft_strlen(args[1]) < 5 && ft_strlen(args[2]) < 5)
		check_lim(l, args, x, y);
	else
	{
		l->res.x = x;
		l->res.y = y;
	}
	free_maker(args);
	return (0);
}

int		parse_textures(char *line, t_all *l)
{
	char	**args;

	args = ft_split(line, ' ');
	if (numw(args) != 2 || check_file(args[1]) == -1)
	{
		free_maker(args);
		print_error("something wrong with specifiers");
	}
	if (!ft_strncmp(args[0], "NO", 2) && (!l->txtrs.path_no))
		l->txtrs.path_no = ft_strdup(args[1]);
	else if (!ft_strncmp(args[0], "WE", 2) && (!l->txtrs.path_we))
		l->txtrs.path_we = ft_strdup(args[1]);
	else if (!ft_strncmp(args[0], "EA", 2) && (!l->txtrs.path_ea))
		l->txtrs.path_ea = ft_strdup(args[1]);
	else if (!ft_strncmp(args[0], "SO", 2) && (!l->txtrs.path_so))
		l->txtrs.path_so = ft_strdup(args[1]);
	else if (!ft_strncmp(args[0], "S", 1) && (!l->txtrs.path_sp))
		l->txtrs.path_sp = ft_strdup(args[1]);
	else
		print_error("something wrong with specifiers");
	free_maker(args);
	return (0);
}

int		parse_color(char *line, t_all *l)
{
	char	**nb;

	(check_coma(line) == -1) ?
	print_error("someting wrong with color") : 0;
	nb = splitset(line, ", ");
	if (!ft_strncmp(nb[0], "F", 1) && numw(nb) == 4)
	{
		if (!digs(nb[1]) && !digs(nb[2]) && !digs(nb[3]) &&
		((l->color.f = create_rgb(ft_atoi(nb[1]),
		ft_atoi(nb[2]), ft_atoi(nb[3]))) != -1))
			l->flags.f_flag = 1;
		else
			print_error("something wrong with color");
	}
	else if (!ft_strncmp(nb[0], "C", 1) && numw(nb) == 4)
	{
		if (!digs(nb[1]) && !digs(nb[2]) && !digs(nb[3]) &&
		((l->color.c = create_rgb(ft_atoi(nb[1]),
		ft_atoi(nb[2]), ft_atoi(nb[3]))) != -1))
			l->flags.c_flag = 1;
		else
			print_error("something wrong with color");
	}
	free_maker(nb);
	return (0);
}

int		parse_line(char *line, t_all *l)
{
	int		i;

	i = skipspaces(line);
	if (line[i] == 'R' && line[i + 1] == ' ')
		return (parse_res(line, l));
	else if ((line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ') ||
			(line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ') ||
			(line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ') ||
			(line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ') ||
			(line[i] == 'S' && line[i + 1] == ' '))
		return (parse_textures(line, l));
	else if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		return (parse_color(line, l));
	else if (line[i] == '\0' || line[i] == '\t')
		return (1);
	return (print_error("something wrong with specifier"));
}

int		parser(char *str, t_all *l)
{
	char	*line;
	int		rd;
	int		fd;
	int		j;

	j = 0;
	init_flags(l);
	data_nulling(l);
	if ((fd = open(str, O_RDONLY)) == -1)
		print_error("cannot open map.cub");
	while ((rd = get_next_line(fd, &line)) && j < 8)
	{
		(line[0] != '\0' && parse_line(line, l) != 1) ? (j++) : 0;
		free(line);
	}
	read_map(fd, line, l);
	return ((rd < 0 || j != 8 || check_flag(l) < 0) ? -1 : 0);
}
