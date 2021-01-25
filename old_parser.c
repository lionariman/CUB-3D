#include "cub.h"

// float	ft_atof(char *line, char c)
// {
// 	float 	num;
// 	char	**args;
// 	int		i;

// 	i = 0;
// 	args = ft_split(line, c);
// 	num = ft_atoi(args[0]);
// 	while (args[1][i])
// 		i++;
// 	num += (ft_atoi(args[1]) / pow(10, i));
// 	free_maker(args);
// 	return (num);
// }

void	data_nulling(t_all *f)
{
	f->res.x = 0;
	f->res.y = 0;
	f->txtrs.path_no = NULL;
	f->txtrs.path_we = NULL;
	f->txtrs.path_ea = NULL;
	f->txtrs.path_so = NULL;
	f->txtrs.path_sp = NULL;
	f->color.f[0] = -1;
	f->color.f[1] = -1;
	f->color.f[2] = -1;
	f->color.c[0] = -1;
	f->color.c[1] = -1;
	f->color.c[2] = -1;
}

void	init_flags(t_all *f)
{
	f->flags.r_flag = 0;
	f->flags.no_flag = 0;
	f->flags.we_flag = 0;
	f->flags.ea_flag = 0;
	f->flags.so_flag = 0;
	f->flags.sp_flag = 0;
	f->flags.f_flag = 0;
	f->flags.c_flag = 0;
}

int		print_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(1, "\n", 1);
	return (-1);
	// exit(0);
}

int		skipspaces(char *line)
{
	int i;
	
	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

int		is_digit_str(char *word)
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
	if (f->flags.r_flag == 1 && f->flags.no_flag == 1 && 
		f->flags.we_flag == 1 && f->flags.ea_flag == 1 &&
		f->flags.so_flag == 1 && f->flags.sp_flag == 1 &&
		f->flags.f_flag == 1 && f->flags.c_flag == 1)
		return (0);
	return (-1);
}

int		ft_atoc(char *line, t_all *all)
{
	int		i;
	int		ret;
	char	**str;

	str = ft_split(line, ',');
	i = 0;
	while (str[i])
		i++;
	if (i != 3)
	{
		free_maker(str);
		return (-1);
	}
	i = -1;
	while (++i < 3)
		if (is_digit_str(str[i]) < 0)
			return (-1);
	all->color.r = ft_atoi(str[0]);
	(all->color.r < 0 || all->color.r > 255) ? (ret = -1) : (ret = 0);
	all->color.g = ft_atoi(str[1]);
	(all->color.g < 0 || all->color.g > 255) ? (ret = -1) : (ret = 0);
	all->color.b = ft_atoi(str[2]);
	(all->color.b < 0 || all->color.b > 255) ? (ret = -1) : (ret = 0);
	free_maker(str);
	return (ret);
}

int		parse_res(char *line, t_all *all, int i)
{
	char	**args;

	i = 0;
	args = ft_split(line, ' ');
	while (args[i])
		i++;
	if (i != 3)
	{
		free_maker(args);
		return (-1);
	}
	all->flags.r_flag = 1;
	all->res.x = ft_atoi(args[1]);
	all->res.y = ft_atoi(args[2]);
	all->res.x > 2560 ? all->res.x = 2560 : 0;
	all->res.y > 1440 ? all->res.x = 1440 : 0;
	if (all->res.x > 0 && all->res.y > 0)
	{
		all->res.x < 100 ? all->res.x = 100 : 0;
		all->res.y < 100 ? all->res.y = 100 : 0;
	}
	free_maker(args);
	return (0);
}

int		parse_textures(char *line, t_all *all, int i)
{
	char	**args;

	i = 0;
	args = ft_split(line, ' ');
	while (args[i])
		i++;
	if (i != 2)
	{
		free_maker(args);
		return (-1);
	}
	if (!ft_strncmp(args[0], "NO", 2) && (!all->flags.no_flag) && 
	(all->txtrs.path_no = args[1]))
		all->flags.no_flag = 1;
	if (!ft_strncmp(args[0], "WE", 2) && (!all->flags.we_flag) && 
	(all->txtrs.path_we = args[1]))
		all->flags.we_flag = 1;
	if (!ft_strncmp(args[0], "EA", 2) && (!all->flags.ea_flag) && 
	(all->txtrs.path_ea = args[1]))
		all->flags.ea_flag = 1;
	if (!ft_strncmp(args[0], "SO", 2) && (!all->flags.so_flag) && 
	(all->txtrs.path_so = args[1]))
		all->flags.so_flag = 1;
	if (!ft_strncmp(args[0], "S", 1) && (!all->flags.sp_flag) && 
	(all->txtrs.path_sp = args[1]))
		all->flags.sp_flag = 1;
	// free_maker(args);
	return (0);
}

int		parse_color(char *line, t_all *all, int i)
{
	char 	**args;

	i = 0;
	args = ft_split(line, ' ');
	while (args[i])
		i++;
	if (i != 2)
	{
		free_maker(args);
		return (-1);
	}
	if (!ft_strncmp(args[0], "F", 1) && !ft_atoc(args[1], all))
	{
		all->color.f[0] = all->color.r;
		all->color.f[1] = all->color.g;
		all->color.f[2] = all->color.b;
		all->flags.f_flag = 1;
	}
	else if (!ft_strncmp(args[0], "C", 1) && !ft_atoc(args[1], all))
	{
		all->color.c[0] = all->color.r;
		all->color.c[1] = all->color.g;
		all->color.c[2] = all->color.b;
		all->flags.c_flag = 1;
	}
	free_maker(args);
	return (0);
}

int		parse_line(char *line, t_all *all)
{
	int		i;

	i = skipspaces(line);
	if (line[i] == 'R' && line[i + 1] == ' ')
		return (parse_res(line, all, i));
	else if ((line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ') ||
			(line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ') ||
			(line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ') ||
			(line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ') ||
			(line[i] == 'S' && line[i + 1] == ' '))
			return (parse_textures(line, all, i));
	else if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		return (parse_color(line, all, i));
	return (print_error("specificators are absend"));
}

int		parser(char *str, t_all *all)
{
	char	*line;
	int		rd;
	int		fd;
	int		j;

	line = NULL;
	j = 0;
	data_nulling(all);
	init_flags(all);
	if((fd = open(str, O_RDONLY)) == -1)
		return (-1);
	while ((rd = get_next_line(fd, &line)) && j < 8)
	{
		if (line[0] != '\0' && parse_line(line, all) != -1)
			j++;
		free(line);
	}
	free(line);
	//map(fd, &line, all);
	close(fd);
	return ((rd < 0 || j != 8 || check_flags(all)) ? -1 : 0);
}
