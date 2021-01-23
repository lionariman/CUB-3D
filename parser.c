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

// t_color	ft_atoc(char *line, char c)
// {
// 	char	**args;
// 	t_color	color;
// 	int		i;

// 	i = 0;
// 	args = ft_split(line, c);
// 	while (args[i])
// 		i++;
// 	// if (i != 3)
// 	// 	return (0);
// 	color.red = ft_atoi(args[0]);
// 	color.green = ft_atoi(args[1]);
// 	color.blue = ft_atoi(args[2]);
// 	free_maker(args);
// 	return (color);
// }

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

// int		parse_line(char *line, t_all *all)
// {
// 	if (line[0] == 'R' && line[1] == ' ')
// 		return (parse_res(line, all));
// 	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
// 		return (parse_texture(line, all));
// 	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
// 		return (parse_texture(line, all));
// 	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
// 		return (parse_texture(line, all));
// 	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
// 		return (parse_texture(line, all));
// 	else if (line[0] == 'S' && line[1] == ' ')
// 		return (parse_texture(line, all));
// 	else if (line[0] == 'F' && line[1] == ' ')
// 		return (parse_floor_ceilling(line, all));
// 	else if (line[0] == 'C' && line[1] == ' ')
// 		return (parse_floor_ceilling(line, all));
// 	return (-1);
// }

void	error(char *str)
{
	write(2, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(0);
}

t_all	*zero_flags(void)
{
	t_all *f;

	f->flags.r_flag = 0;
	f->flags.no_flag = 0;
	f->flags.so_flag = 0;
	f->flags.we_flag = 0;
	f->flags.ea_flag = 0;
	f->flags.s_flag = 0;
	f->flags.f_flag = 0;
	f->flags.c_flag = 0;
	return (f);
}

int		parse_res(char *line, t_all *all)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_split(line, ' ');
	while (args[i])
		i++;
	if (i != 3)
		return (-1);
	// (*scene)->viewport.width = ft_atoi(args[1]);
	// (*scene)->viewport.height = ft_atoi(args[2]);
	return (0);
}

int		parse_line(char *line, t_all *all)
{
	char	**words;
	int		i;

	i = 0;
	words = ft_split(line, ' ');
	while (words[i])
	{
		if (ft_strncmp(words[i], "R", 1) && !all->flags.r_flag)
			return (parse_res(line, all))
		else if (ft_strncmp(words[i], "NO", 2) && !all->flags.no_flag)
			return (parse_texture(line, all));
		else if (ft_strncmp(words[i], "SO", 2) && !all->flags.so_flag)
			return (parse_texture(line, all));
		else if (ft_strncmp(words[i], "WE", 2) && !all->flags.we_flag)
			return (parse_texture(line, all));
		else if (ft_strncmp(words[i], "EA", 2) && !all->flags.ea_flag)
			return (parse_texture(line, all));
		else if (ft_strncmp(words[i], "S", 1) && !all->flags.s_flag)
			return (parse_texture(line, all));
		else if (ft_strncmp(words[i], "F", 1) && !all->flags.f_flag)
			return (parse_floor_ceilling(line, all));
		else if (ft_strncmp(words[i], "C", 1) && !all->flags.c_flag)
			return (parse_floor_ceilling(line, all));
		i++;
	}
}

int		parser(char *str, t_all *all)
{
	char	*line;
	int		i;
	int		fd;

	line = NULL;
	i = 0;
	if((fd = open(str, O_RDONLY)) < 0)
		error("fd error");
	while ((get_next_line(fd, &line)) && i < 7)
	{
		if ((parse_line(line, all)) == -1)
			return ("parse error");
		free(line);
	}
	return (0);
}

//----------------------------------------------------