#include "cub.h"

int		main(int argc, char **argv)
{
	t_all	all;
	t_list	*head;
	int		i;

	if (argc > 3 || argc < 2)
		return (print_error("error: wrong number of arguments"));
	if ((parser(argv[1], &all)) == -1)
		return (print_error("undefined error"));

	//---------------------<test>---------------------
	write(1, "\n", 1);
	printf("|res x:    %d|\n", all.res.x);
	printf("|res y:    %d|\n", all.res.y);
	printf("|path no:  %s|\n", all.txtrs.path_no);
	printf("|path we:  %s|\n", all.txtrs.path_we);
	printf("|path ea:  %s|\n", all.txtrs.path_ea);
	printf("|path so:  %s|\n", all.txtrs.path_so);
	printf("|path sp:  %s|\n", all.txtrs.path_sp);
	printf("|f:        %d|\n", all.color.f);
	printf("|c:        %d|\n", all.color.c);
	printf("|r flag:   %d|\n", all.flags.r_flag);
	printf("|f flag:   %d|\n", all.flags.f_flag);
	printf("|c flag:   %d|\n", all.flags.c_flag);
	printf("|s flag:   %d|\n", all.flags.s_flag);
	printf("|pos  x:  %lf|\n", all.plr.pos_x);
	printf("|pos  y:  %lf|\n", all.plr.pos_y);
	printf("|dir  x:  %lf|\n", all.plr.dir_x);
	printf("|dir  y:  %lf|\n", all.plr.dir_y);
	printf("|plane x: %lf|\n", all.plane.x);
	printf("|plane y: %lf|\n", all.plane.y);
	// printf("|%d, %d|\n", all.w, all.h);
	write(1, "\n", 1);
	// i = -1;
	// while (++i < 16)
	// 	printf("|%lf,%lf|\n", all.sp[i].x, all.sp[i].y);
	// write(1, "\n", 1);
	i = -1;
	while (all.map[++i])
		ft_putendl_fd(all.map[i], 1);
	cub(&all);
	// free_maker(all.map);
	// while (1);
	//---------------------<test>---------------------

	// mlx_key_hook(all.win.mlx, key_hook, &all.win);
	return (0);
}