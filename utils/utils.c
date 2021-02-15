/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:49:28 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/15 19:29:35 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_maker(char **line)
{
	int i;

	i = -1;
	while (line[++i] != NULL)
		free(line[i]);
	free(line);
}

int		print_error(char *str)
{
	write(1, "Error:\n", 7);
	write(2, str, ft_strlen(str));
	exit(0);
}

int		num_of_words(char **words)
{
	int i;

	i = 0;
	while (words[i])
		i++;
	return (i);
}

int		digs(char *word)
{
	int i;

	i = -1;
	while (word[++i])
		if (!ft_isdigit(word[i]))
			return (-1);
	return (0);
}

int		create_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255 ||
		g < 0 || g > 255 ||
		b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}
