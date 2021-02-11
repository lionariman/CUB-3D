#include "cub.h"

int		parse_res(char *line, t_all *all)
{
	char	**args;

	args = ft_split(line, ' ');
	if (num_of_words(args) != 3)
	{
		free_maker(args);
		return (print_error("error: wrong number of arguments"));
	}
	all->flags.r_flag = 1;
	all->res.x = ft_atoi(args[1]);
	all->res.y = ft_atoi(args[2]);
	all->res.x > 2560 ? all->res.x = 2560 : 0;
	all->res.y > 1440 ? all->res.y = 1440 : 0;
	if (all->res.x < 100 && all->res.y < 100)
	{
		all->res.x < 100 ? all->res.x = 100 : 0;
		all->res.y < 100 ? all->res.y = 100 : 0;
	}
	free_maker(args);
	return (0);
}

int		parse_textures(char *line, t_all *all)
{
	char	**args;

	args = ft_split(line, ' ');
	if (num_of_words(args) != 2 || check_file(args[1]) == -1)
	{
		free_maker(args);
		return (print_error("error: wrong number of arguments"));
	}
	if (!ft_strncmp(args[0], "NO", 2) && (!all->txtrs.path_no))
		all->txtrs.path_no = ft_strdup(args[1]);
	else if (!ft_strncmp(args[0], "WE", 2) && (!all->txtrs.path_we))
		all->txtrs.path_we = ft_strdup(args[1]);
	else if (!ft_strncmp(args[0], "EA", 2) && (!all->txtrs.path_ea))
		all->txtrs.path_ea = ft_strdup(args[1]);
	else if (!ft_strncmp(args[0], "SO", 2) && (!all->txtrs.path_so))
		all->txtrs.path_so = ft_strdup(args[1]);
	else if (!ft_strncmp(args[0], "S", 1) && (!all->txtrs.path_sp))
		all->txtrs.path_sp = ft_strdup(args[1]);
	else
		return (print_error("error: something went wrong"));
	free_maker(args);
	return (0);
}

int		parse_color(char *line, t_all *all)
{
	char 	**nb;

	nb = splitset(line, ", ");
	if (!ft_strncmp(nb[0], "F", 1) && num_of_words(nb) == 4)
	{
		if (!digs(nb[1]) && !digs(nb[2]) && !digs(nb[3]) &&
		((all->color.f = create_rgb(ft_atoi(nb[1]),
		ft_atoi(nb[2]), ft_atoi(nb[3]))) != -1))
			all->flags.f_flag = 1;
		else
			return (print_error("error: something wrong with color"));
	}
	else if (!ft_strncmp(nb[0], "C", 1) && num_of_words(nb) == 4)
	{
		if (!digs(nb[1]) && !digs(nb[2]) && !digs(nb[3]) &&
		((all->color.c = create_rgb(ft_atoi(nb[1]),
		ft_atoi(nb[2]), ft_atoi(nb[3]))) != -1))
			all->flags.c_flag = 1;
		else
			return (print_error("error: something wrong with color"));
	}
	free_maker(nb);
	return (0);
}

int		parse_line(char *line, t_all *all)
{
	int		i;

	i = skipspaces(line);
	if (line[i] == 'R' && line[i + 1] == ' ')
		return (parse_res(line, all));
	else if ((line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ') ||
			(line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ') ||
			(line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ') ||
			(line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ') ||
			(line[i] == 'S' && line[i + 1] == ' '))
			return (parse_textures(line, all));
	else if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		return (parse_color(line, all));
	else if (line[i] == '\0' || line[i] == '\t')
		return (1);
	return (print_error("error: something wrong with specifier"));
}

int		parser(char *str, t_all *all)
{
	char	*line;
	int		rd;
	int		fd;
	int		j;

	j = 0;
	init_flags(all);
	data_nulling(all);
	if((fd = open(str, O_RDONLY)) == -1)
		return (-1);
	while ((rd = get_next_line(fd, &line)) && j < 8)
	{
		(line[0] != '\0' && parse_line(line, all) != 1) ? (j++) : 0;
		free(line);
	}
	read_map(fd, line, all);
	return ((rd < 0 || j != 8 || check_flag(all) < 0) ? -1 : 0);
}
