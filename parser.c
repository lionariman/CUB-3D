#include "cub.h"

int		store_map(t_list **head, t_all *all, int size)
{
	int		i;
	t_list	*tmp;

	if (!(all->map = ft_calloc(size + 1, sizeof(char *))))
		return (-1);
	i = -1;
	tmp = *head;
	while (tmp)
	{
		all->map[++i] = tmp->content;
		tmp = tmp->next;
	}
	all->map[i] = NULL;
	// i = -1;
	// while (all->map[++i])
	// 	ft_putendl_fd(all->map[i], 1);
	ft_lstclear(head, &free);
	return (0);
}

int		read_map(char *str, t_list **head)
{
	char	*line;
	int		fd;

	*head = NULL;
	line = NULL;
	if ((fd = open(str, O_RDONLY)) == -1)
		return (-1);
	while ((get_next_line(fd, &line)) > 0)
		ft_lstadd_back(head, ft_lstnew(line));
	ft_lstadd_back(head, ft_lstnew(line));
	free(line);
	return (0);
}

//------------------main-parser-----------------------


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

// void	error(char *str)
// {
// 	write(2, str, ft_strlen(str));
// 	write(1, "\n", 1);
// 	exit(0);
// }

// void	zero_flags(t_all *f)
// {
// 	f->flags.r_flag = 0;
// 	f->flags.no_flag = 0;
// 	f->flags.so_flag = 0;
// 	f->flags.we_flag = 0;
// 	f->flags.ea_flag = 0;
// 	f->flags.s_flag = 0;
// 	f->flags.f_flag = 0;
// 	f->flags.c_flag = 0;
// }

int		skipspaces(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}

int		is_digit_str(char *word)
{
	int i;
​
	i = 0;
	while (word[i])
		if (!ft_isdigit(word[i]))
			return (-1);
		i++;
	return	(0);
}

int		ft_atoc(char *line, t_all *all)
{
	int i;
	char **str;
​
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
	while (i < 3)
	{
		if (!is_digit_str(str[++i]))
			return (-1);
	}
	all->color.r = ft_atoi(str[0]);
	if (all->color.r  < 0 && all->color.r > 255)
		return (-1);
	all->color.g = ft_atoi(str[1]);
	if (all->color.g  < 0 && all->color.g > 255)
		return(-1);
	all->color.b = ft_atoi(str[2]);
	if (all->color.b  < 0 && all->color.b > 255)
		return (-1);
	return (0);
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
	all->res.x = ft_atoi(args[1]);
	all->res.y = ft_atoi(args[2]);
	if (all->res.x > 2560)
		all->res.x = 2560;
	if (all->res.y > 1440)
		all->res.x = 1440;
	if (all->res.x > 0 && all->res.y > 0)
	{
		if (all->res.x < 100)
			all->res.x = 100;
		if (all->res.y < 100)
			all->res.y = 100;
	}
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
	(!ft_strncmp(args[0], "NO", 2)) ? (all->txtrs.no_path = args[1]) : 0;
	(!ft_strncmp(args[0], "WE", 2)) ? (all->txtrs.we_path = args[1]) : 0;
	(!ft_strncmp(args[0], "EA", 2)) ? (all->txtrs.ea_path = args[1]) : 0;
	(!ft_strncmp(args[0], "SO", 2)) ? (all->txtrs.so_path = args[1]) : 0;
	(!ft_strncmp(args[0], "S", 1)) ? (all->txtrs.sp_path = args[1]) : 0;
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
	if (!(ft_strncmp(args[0], "F", 1)) && !ft_atoc(args[1], all))
	{
		all->color.f[0] = all->color.r;
		all->color.f[1] = all->color.g;
		all->color.f[2] = all->color.b;
	}
	else if (!(ft_strncmp(args[0], "C", 1)) && !ft_atoc(args[1], all))
	{
		all->color.c[0] = all->color.r;
		all->color.c[1] = all->color.g;
		all->color.c[2] = all->color.b;
	}
	free_maker(args);
	return (0);
}

int		parse_line(char *line, t_all *all)
{
	int i;

	i = 0;
	i = skipspaces(line, i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		return (parse_res(line, all, i));
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (parse_textures(line, all, i));
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		return (parse_textures(line, all, i));
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		return (parse_textures(line, all, i));
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (parse_textures(line, all, i));
	if (line[i] == 'S' && line[i + 1] == ' ')
		return (parse_textures(line, all, i));
	if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		return (parse_color(line, all, i));
	return (-1);
}

int		parser(char *str, t_all *all)
{
	char	*line;
	int		i;
	int		fd;
	int		j;

	line = NULL;
	i = 0;
	j = 0;
	if((fd = open(str, O_RDONLY)) == -1)
		return (-1);
	while ((get_next_line(fd, &line)) && ++j < 8)
	{
		if ((parse_line(line, all)) == -1)
			return (-1);
		free(line);
	}
	close(fd);
	if (j != 8)
		return (-1);
	return (0);
}

//----------------------------------------------------