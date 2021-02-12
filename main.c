/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:06:14 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/12 23:47:16 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		main(int argc, char **argv)
{
	t_all	all;
	t_list	*head;
	int		fd;
	int		i;

	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 6) != 0)
			return (print_error("cub3d works only with \"--save\""));
		if ((fd = open("cub3d.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666)) < 0)
			return (print_error("cannot create a new .bmp file\n"));
		all.flags.bmp = 1;
		parser(argv[1], &all);
		all.win.mlx = mlx_init();
		raycast(&all);
		create_bmp(&all, fd);
		close(fd);
		exit(0);
	}
	else if (argc == 2 && (parser(argv[1], &all)) != -1)
		cub(&all);
	else
		return (print_error("something is wromg"));
	// i = -1;
	// while (all.map[++i])
	// 	ft_putendl_fd(all.map[i], 1);
	return (0);
}