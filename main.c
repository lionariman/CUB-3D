#include "cub.h"

int		make_bitmap(t_all *l)
{
	int				fd;
	unsigned int	n = 0;
	signed int		s = 0;
	unsigned int	size = 0;

	if ((fd = open("cub3d.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666)) < 0)
		 return (print_error("cannot create a new .bmp file\n"));
	write(fd, "BM", 2);
	size = 54 + (l->res.x * l->res.y * l->win.bppixel);
	write(fd, &size, 4);
	write(fd, &n, 2);
	write(fd, &n, 2);
	n = 54;
	write(fd, &n, 4);
	n = 40;
	write(fd, &n, 4);
	write(fd, &l->res.x, 4);
	write(fd, &l->res.y, 4);
	n = 1;
	write(fd, &n, 2);
	write(fd, &l->win.bppixel, 2);
	n = 0;
	write(fd, &n, 4);
	write(fd, &n, 4);
	s = 0;
	write(fd, &s, 4);
	write(fd, &s, 4);
	write(fd, &n, 4);
	write(fd, &n, 4);
	s = l->res.y;
	while (s > 0)
	{
		s--;
		write(fd, l->win.addr + (s * l->win.line_len), l->res.x * (l->win.bppixel / 8));
	}
	close(fd);
	exit(0);
}

int		main(int argc, char **argv)
{
	t_all	all;
	t_list	*head;
	int		i;

	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 6) != 0)
			return (print_error("cub3d works only with \"--save\""));
		all.flags.bmp = 1;
		parser(argv[1], &all);
		all.win.mlx = mlx_init();
		raycast(&all);
		make_bitmap(&all);
	}
	else if (argc == 2 && (parser(argv[1], &all)) != -1)
		cub(&all);
	else
		return (0);

	// else
	// 	return (print_error("error: wrong number of arguments"));

	// write(1, "\n", 1);
	// printf("|res x:    %d|\n", all.res.x);
	// printf("|res y:    %d|\n", all.res.y);
	// printf("|path no:  %s|\n", all.txtrs.path_no);
	// printf("|path we:  %s|\n", all.txtrs.path_we);
	// printf("|path ea:  %s|\n", all.txtrs.path_ea);
	// printf("|path so:  %s|\n", all.txtrs.path_so);
	// printf("|path sp:  %s|\n", all.txtrs.path_sp);
	// printf("|f:        %d|\n", all.color.f);
	// printf("|c:        %d|\n", all.color.c);
	// printf("|r flag:   %d|\n", all.flags.r_flag);
	// printf("|f flag:   %d|\n", all.flags.f_flag);
	// printf("|c flag:   %d|\n", all.flags.c_flag);
	// printf("|s flag:   %d|\n", all.flags.s_flag);
	// printf("|pos  x:  %lf|\n", all.plr.pos_x);
	// printf("|pos  y:  %lf|\n", all.plr.pos_y);
	// printf("|dir  x:  %lf|\n", all.plr.dir_x);
	// printf("|dir  y:  %lf|\n", all.plr.dir_y);
	// printf("|plane x: %lf|\n", all.plane.x);
	// printf("|plane y: %lf|\n", all.plane.y);
	// write(1, "\n", 1);
	// i = -1;
	// while (all.map[++i])
	// 	ft_putendl_fd(all.map[i], 1);
	return (0);
}