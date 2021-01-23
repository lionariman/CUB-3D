#include "../includes/cub3d.h"
#define MIN_WIDTH 160
#define MIN_HEIGHT 160
​
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
​
int		parse_res(char *words, t_all *all)
{
	int		i;
​
	i = 0;
	while (words[i])
		i++;
	if (i < 3 || i > 3)
		error("WRONG RESOLUTION!\n");
	if (!ft_strncmp(words[0], "R", 1))
		error("WRONG RESOLUTION!\n");
	if (is_digit_str(words[1]) == -1 || is_digit_str(words[2]) == -1)
		error("WRONG RESOLUTION!");
	if (all->win->win_res.width = ft_atoi(words[1]) < 0)
		error("WRONG RESOLUTION!\n");
	if (all->win->scr_res.width < all->win->win_res.width)
		all->win->win_res.width = all->win->scr_res.width;
	if (all->win->win_res.height = ft_atoi(words[2]) < 0)
		error("WRONG RESOLUTION!\n");
	if (all->win->scr_res.height < all->win->win_res.height)
		all->win->win_res.height = all->win->scr_res.height;
	if (all->win->win_res.height < MIN_HEIGHT
	|| all->win->win_res.width < MIN_WIDTH)
		error("WRONG RESOLUTION!\n");
	return (0);
}
​
int		check_flags(t_all *all)
{
	if (!(all->textures.fd_sprite
	&& all->textures.fd_e
	&& all->textures.fd_w
	&& all->textures.fd_n && all->textures.fd_s))
		return (-1);
	return (0);
}
​
int		parse_textures(char **words, t_all *all)
{
	int		i;
​
	i = 0;
	while (words[i])
		i++;
	if (i != 2)
		error("WRONG TEXTURE PATH!\n");
	if (!(ft_strncmp(*words, "SO", 2)) && (all->textures.flag_s == 0)
	&& (all->textures.fd_s = open(words[1], O_RDONLY) > 0))
		all->textures.flag_s = 1;
	else if (!(ft_strncmp(*words, "S", 1)) && (all->textures.flag_sprite == 0)
	&& (all->textures.fd_sprite = open(words[1], O_RDONLY) > 0))
		all->textures.flag_sprite = 1;
	else if (!(ft_strncmp(*words, "NO", 2)) && (all->textures.flag_n == 0)
	&& (all->textures.fd_n = open(words[1], O_RDONLY) > 0))
		all->textures.flag_n = 1;
	else if (!(ft_strncmp(*words, "WE", 2)) && (all->textures.flag_w == 0)
	&& (all->textures.fd_w = open(words[1], O_RDONLY) > 0))
		all->textures.flag_w = 1;
	else if (!(ft_strncmp(*words, "EA", 2)) && (all->textures.flag_e == 0)
	&& (all->textures.fd_e = open(words[1], O_RDONLY) > 0))
		all->textures.flag_e = 1;
	else
		error("WRONG TEXTURE PATH!\n");
	return (0);
}
​
static void w_free(char **words)
{
	int i;
	int n;
​
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}
​
int		atorgb(char *s, t_rgb *color)
{
	int i;
	char **s1;
​
	s1 = ft_split(s, ',');
	i = 0;
	while (s1[i])
		i++;
	if (i < 3)
		return (-1);
	i = 0;
	while (i++ < 3)
	{
		if (!is_digit_str(s1[i]))
			return (-1);
	}
	color->r = ft_atoi(*s1);
	if (color->r  < 0 && color > 255)
		return (-1);
	s1++;
	color->g = ft_atoi(*s1);
	if (color->g  < 0 && color > 255)
		return(-1);
	s1++;
	color->r = ft_atoi(*s1);
	if (color->g  < 0 && color > 255)
		return (-1);
	return (0);
}
​
int		parse_color(char **words, t_all *all)
{
	int i;
​
	i = 0;
	while (words[i])
		i++;
	if (i != 2)
		error("WRONG COLOR!\n");
	if (!ft_strncmp(words[0], "F", 1) && all->f_flag == 0
	&& atorgb(words[1], &all->floor) == 0)
		all->f_flag = 1;
	else if (!ft_strncmp(words[0], "C", 1) && all->c_flag == 0
	&& atorgb(words[1], &all->celling) == 0)
		all->c_flag = 1;
	else
		error("WRONG COLOR!\n");
	return (0);
}
​
int		parse_conf(char *line, t_list *map, t_all *all)
{
	char **words;
	int ret;
​
	if (!(words = ft_split(*line, ' ')))
		error("WRONG MEMMORY ALLOCATE!\n");
	if (*line == 'R')
		ret = parse_res(words, all);
	else if ((*line == 'S') || (*line == 'N') || (*line == 'W') || (*line = 'E'))
		ret = parse_textures(words, all);
	else if ((*line == 'F') || (*line == 'C'))
		ret = parse_color(words, all);
	w_free(words);
	return (ret);
}
​
int		parser(int fd, char *line, t_list **map, t_all *all)
{
	int	readed_b;
	int i;
​
	i = 8;
	while ((readed_b = get_next_line(fd, &line)) > 0 && (check_flags(all) < 0) && i < 8)
	{
		if (readed_b = -1)
			error("SOMTHING WRONG WITH '.cub' FILE!\n");
		parse_conf(line, map, all);
	}
	if (check_flags(all) < 0)
		error("WRONG NUMBER OF SPECIFICATORS!\n");
	while ((readed_b = get_next_line(fd, &line)) > 0 && (check_flags(all) < 0))
	{
		
	}
	if (readed_b = -1)
		error("SOMTHING WRONG WITH '.cub' FILE!\n");
	return (0);
}