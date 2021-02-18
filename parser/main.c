/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:06:14 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/18 12:16:36 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		main(int argc, char **argv)
{
	t_all	all;
	int		fd;

	all.win.mlx = mlx_init();
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) != 0 ||
			ft_strncmp(argv[1], "map.cub", ft_strlen(argv[1])) != 0)
			print_error("wrong name of argument");
		if ((fd = open("cub3D.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666)) < 0)
			print_error("Cannot create a bmp file");
		parser(argv[1], &all);
		all.flags.bmp = 1;
		get_img(&all);
		get_addr(&all);
		raycast(&all);
		create_bmp(&all, fd);
	}
	else if (argc == 2 && !ft_strncmp(argv[1], "map.cub", 7) &&
	(parser(argv[1], &all)) != -1)
		cub(&all);
	else
		print_error("Something is wrong");
	return (0);
}
