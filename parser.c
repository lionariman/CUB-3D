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
	f->plane.x = 0;
	f->plane.y = 0;
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
}

void	free_maker(char **line)
{
	int i;

	i = -1;
	while (line[++i] != NULL)
		free(line[i]);
	free(line);
}

int		print_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(0);
	// return (-1);
}

int		skipspaces(char *line)
{
	int i;
	
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

int		num_of_words(char **words)
{
	int i;

	i = 0;
	while (words[i])
		i++;
	return (i);
}

int		digs(char *word)
{
	int i;

	i = -1;
	while (word[++i])
		if (!ft_isdigit(word[i]))
			return (-1);
	return (0);
}

int		check_flags(t_all *f)
{
	if (f->flags.r_flag == 1 && f->flags.f_flag == 1 && f->flags.c_flag == 1)
		return (0);
	return (-1);
}

int		parse_res(char *line, t_all *all)
{
	char	**args;

	args = ft_split(line, ' ');
	if (num_of_words(args) != 3)
	{
		free_maker(args);
		return (-1);
	}
	all->flags.r_flag = 1;
	all->res.x = ft_atoi(args[1]);
	all->res.y = ft_atoi(args[2]);
	all->res.x > 2560 ? all->res.x = 2560 : 0;
	all->res.y > 1440 ? all->res.y = 1440 : 0;
	if (all->res.x < 200 && all->res.y < 200)
	{
		all->res.x < 200 ? all->res.x = 200 : 0;
		all->res.y < 200 ? all->res.y = 200 : 0;
	}
	free_maker(args);
	return (0);
}

int		parse_textures(char *line, t_all *all)
{
	char	**args;

	args = ft_split(line, ' ');
	if (num_of_words(args) != 2)
	{
		free_maker(args);
		return (-1);
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
	free_maker(args);
	return (0);
}

int		parse_color(char *line, t_all *all)
{
	char 	**nb;

	nb = splitset(line, ", ");
	if (!ft_strncmp(nb[0], "F", 1) && num_of_words(nb) == 4)
	{
		if (!digs(nb[1]) && !digs(nb[2]) && !digs(nb[3]))
			all->color.f = (ft_atoi(nb[1]) << 16 |
			ft_atoi(nb[2]) << 8 | ft_atoi(nb[3]));
		else
			return (-1);
		all->flags.f_flag = 1;
	}
	else if (!ft_strncmp(nb[0], "C", 1) && num_of_words(nb) == 4)
	{
		if (!digs(nb[1]) && !digs(nb[2]) && !digs(nb[3]))
			all->color.c = (ft_atoi(nb[1]) << 16 |
			ft_atoi(nb[2]) << 8 | ft_atoi(nb[3]));
		else
			return (-1);
		all->flags.c_flag = 1;
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
	return (print_error("specifier error"));
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
	return ((rd < 0 || j != 8 || check_flags(all) < 0) ? -1 : 0);
}
