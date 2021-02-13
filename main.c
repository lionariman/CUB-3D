/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:06:14 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/13 10:20:40 by keuclide         ###   ########.fr       */
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
			return (print_error("Cub3d works only with \"--save\""));
		if ((fd = open("cub3d.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666)) < 0)
			return (print_error("Cannot create a new .bmp file\n"));
		all.flags.bmp = 1;
		parser(argv[1], &all);
		all.win.mlx = mlx_init();
		raycast(&all);
		create_bmp(&all, fd);
	}
	else if (argc == 2 && (parser(argv[1], &all)) != -1)
		cub(&all);
	else
		return (print_error("Something is wrong"));
	return (0);
}