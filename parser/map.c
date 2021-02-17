/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:37:40 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/17 10:11:30 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_map(t_all *l)
{
	int i;
	int j;

	i = -1;
	while (l->map[++i])
	{
		j = -1;
		while (l->map[i][++j])
		{
			if (!check_arg("012NWES ", l->map[i][j]))
			{
				if (!check_arg("NWES", l->map[i][j]))
				{
					player_pos(l, i, j);
					l->flags.p_flag++;
				}
				(!check_arg("2", l->map[i][j])) ? l->flags.s_flag++ : 0;
			}
			else
				return (-1);
		}
		if (j == 0)
			return (-1);
	}
	return ((l->flags.p_flag > 1 || !l->flags.p_flag) ? -1 : 0);
}

int		check_around(t_all *l, int i, int j)
{
	j++;
	while (l->map[i][j] && (size_t)j < (ft_strlen(l->map[i]) - 1))
	{
		if (!check_arg("02NWES", l->map[i][j]))
			if (check_arg("012NWES", l->map[i][j + 1]) == -1 ||
				check_arg("012NWES", l->map[i][j - 1]) == -1 ||
				check_arg("012NWES", l->map[i - 1][j]) == -1 ||
				check_arg("012NWES", l->map[i + 1][j]) == -1 ||
				check_arg("012NWES", l->map[i + 1][j + 1]) == -1 ||
				check_arg("012NWES", l->map[i + 1][j - 1]) == -1 ||
				check_arg("012NWES", l->map[i - 1][j + 1]) == -1 ||
				check_arg("012NWES", l->map[i - 1][j - 1]) == -1)
				return (-1);
		j++;
	}
	return (0);
}

int		parse_map(t_all *l)
{
	int i;
	int j;

	i = 0;
	j = -1;
	while (l->map[i][++j])
		if (!check_arg("02NWES", l->map[i][j]))
			return (-1);
	while (l->map[++i])
	{
		j = skipspaces(l->map[i]);
		if (!check_arg("02NWES", l->map[i][j]))
			return (-1);
		if (check_around(l, i, j) == -1)
			return (-1);
		j = ft_strlen(l->map[i]) - 1;
		if (!check_arg("02NWES", l->map[i][j]))
			return (-1);
	}
	j = -1;
	i = skiplines(l->map);
	while (l->map[i][++j])
		if (!check_arg("02NWES", l->map[i][j]))
			return (-1);
	return (0);
}

int		store_map(t_list **head, t_all *l, int size)
{
	t_list	*tmp;
	int		i;
	int		f;

	i = 0;
	f = 0;
	tmp = *head;
	if (!(l->map = ft_calloc(size + 1, sizeof(char *))))
		print_error("cannot allocate memory for map");
	while (tmp && size > 0)
	{
		if (ft_strlen(tmp->content))
		{
			l->map[i++] = ft_strdup(tmp->content);
			size--;
			f = 1;
		}
		if (!ft_strlen(tmp->content) && f == 1)
			print_error("something went wrong");
		free(tmp->content);
		tmp = tmp->next;
	}
	l->map[i] = NULL;
	ft_lstclear(head, &free);
	return (0);
}

int		read_map(int fd, char *line, t_all *l)
{
	t_list	*head;
	int		i;

	i = 0;
	head = NULL;
	line[0] != '\0' ? (i++) : 0;
	ft_lstadd_back(&head, ft_lstnew(line));
	while (get_next_line(fd, &line) > 0)
	{
		line[0] != '\0' ? (i++) : 0;
		ft_lstadd_back(&head, ft_lstnew(line));
	}
	line[0] != '\0' ? (i++) : 0;
	ft_lstadd_back(&head, ft_lstnew(line));
	if (store_map(&head, l, i) == -1)
		print_error("cannot locate memory");
	if (check_map(l) == -1)
		print_error("something wrong with map");
	if (parse_map(l) == -1)
		print_error("map is not closed");
	close(fd);
	return (0);
}
