#include "cub.h"

// t_all	*init_all(void)
// {
// 	t_all *all;

// 	if (!(all = malloc(sizeof(t_all))))
// 		return (NULL);
// 	all->win->mlx = NULL;
// 	all->win->win = NULL;
// 	all->plr->x = 0;
// 	all->plr->y = 0;
// 	all->plr->start = 0;
// 	all->plr->end = 0;
// 	all->plr->dir = 0;
// 	all->map = NULL;
// 	return (all);
// }


void	free_maker(char **line)
{
	int i;

	i = -1;
	while (line[++i])
		free(line[i]);
	free(line);
}

void	my_mlx_pixel_put(t_wndw *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bppixel / 8));
	*(unsigned int *)dst = color;
}

int		key_hook(int keycode, t_wndw *win)
{
	if (keycode == 53)
		mlx_destroy_window(win->mlx, win->win);
	return (0);
}

void	scale_map(t_all all)
{
	t_point end;

	end.x = (all.point.x + 1) * SCALE;
	end.y = (all.point.y + 1) * SCALE;
	all.point.x *= SCALE;
	all.point.y *= SCALE;
	while (all.point.y < end.y)
	{
		while (all.point.x < end.x)
		{
			mlx_pixel_put(all.win.mlx, all.win.win, all.point.x, all.point.y, 0x0F0FFF);
			all.point.x++;
		}
		all.point.x -= SCALE;
		all.point.y++;
	}
}

void	draw_map(t_all *all)
{
	all->win.mlx = mlx_init();
	all->win.win = mlx_new_window(all->win.mlx, screenWidth, screenHeight, "Wolfenstein");

	all->point.y = 0;
	while (all->map[all->point.y])
	{
		all->point.x = 0;
		while (all->map[all->point.y][all->point.x])
		{
			if (all->map[all->point.y][all->point.x] == '1')
				scale_map(*all);
			all->point.x++;
		}
		all->point.y++;
	}
	mlx_loop(all->win.mlx);
}

int		main(int argc, char **argv)
{
	t_all	all;
	t_list	*head;
	int		i;

	if (argc > 3 || argc < 2)
		return (print_error("wrong number of arguments"));
	if ((parser(argv[1], &all)) == -1)
		return (print_error("parse error"));


	//----------------------test----------------------
	printf("|res:     %d|\n", all.res.x);
	printf("|res:     %d|\n", all.res.y);
	printf("|path_no: %s|\n", all.txtrs.path_no);
	printf("|path_we: %s|\n", all.txtrs.path_we);
	printf("|path_ea: %s|\n", all.txtrs.path_ea);
	printf("|path_so: %s|\n", all.txtrs.path_so);
	printf("|path_sp: %s|\n", all.txtrs.path_sp);
	printf("|f_red:   %d|\n", all.color.f[0]);
	printf("|f_green: %d|\n", all.color.f[1]);
	printf("|f_blue:  %d|\n", all.color.f[2]);
	printf("|c_red:   %d|\n", all.color.c[0]);
	printf("|c_green: %d|\n", all.color.c[1]);
	printf("|c_blue:  %d|\n", all.color.c[2]);
	printf("|red:     %d|\n", all.color.r);
	printf("|green:   %d|\n", all.color.g);
	printf("|blue:    %d|\n", all.color.b);
	printf("----flags----\n");
	printf("|r_flag:  %d|\n", all.flags.r_flag);
	printf("|no_flag: %d|\n", all.flags.no_flag);
	printf("|we_flag: %d|\n", all.flags.we_flag);
	printf("|ea_flag: %d|\n", all.flags.ea_flag);
	printf("|so_flag: %d|\n", all.flags.so_flag);
	printf("|sp_flag: %d|\n", all.flags.sp_flag);
	printf("|f_flag:  %d|\n", all.flags.f_flag);
	printf("|c_flag:  %d|\n", all.flags.c_flag);
	//------------------------------------------------

	// if ((read_map(argv[1], &head)) == -1)
	// 	return (-1);
	// if ((store_map(&head, &all, ft_lstsize(head))) == -1)
	// 	return (-1);

	// i = 0;
	// while (all.map[i])
	// 	ft_putendl_fd(all.map[i++], 1);

	// draw_map(&all);
	// mlx_key_hook(all.win.mlx, key_hook, &all.win);
	return (0);
}