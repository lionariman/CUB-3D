/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:37:40 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/13 11:49:54 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_map(t_all *all)
{
	int i;
	int j;

	i = -1;
	while (all->map[++i])
	{
		j = -1;
		while (all->map[i][++j])
		{
			if (!check_arg("012NWES ", all->map[i][j]))
			{
				if (!check_arg("NWES", all->map[i][j]))
				{
					player_pos(all, i, j);
					all->flags.p_flag++;
				}
				(!check_arg("2", all->map[i][j])) ? all->flags.s_flag++ : 0;
			}
			else
				return (-1);
		}
		if (j == 0)
			return (-1);
	}
	return ((all->flags.p_flag > 1 || !all->flags.p_flag) ? -1 : 0);
}

int		check_around(t_all *all, int i, int j)
{
	j++;
	while (all->map[i][j] && j < ft_strlen(all->map[i]) - 1)
	{
		if (!check_arg("02NWES", all->map[i][j]))
			if (check_arg("012NWES", all->map[i][j + 1]) == -1 ||
				check_arg("012NWES", all->map[i][j - 1]) == -1 ||
				check_arg("012NWES", all->map[i - 1][j]) == -1 ||
				check_arg("012NWES", all->map[i + 1][j]) == -1 ||
				check_arg("012NWES", all->map[i + 1][j + 1]) == -1 ||
				check_arg("012NWES", all->map[i + 1][j - 1]) == -1 ||
				check_arg("012NWES", all->map[i - 1][j + 1]) == -1 ||
				check_arg("012NWES", all->map[i - 1][j - 1]) == -1)
				return (-1);
		j++;
	}
	return (0);
}

int		parse_map(t_all *all)
{
	int i;
	int j;

	i = 0;
	j = -1;
	while (all->map[i][++j])
		if (!check_arg("02NWES", all->map[i][j]))
			return (-1);
	while (all->map[++i])
	{
		j = skipspaces(all->map[i]);
		if (!check_arg("02NWES", all->map[i][j]))
			return (-1);
		if (check_around(all, i, j) == -1)
			return (-1);
		j = ft_strlen(all->map[i]) - 1;
		if (!check_arg("02NWES", all->map[i][j]))
			return (-1);
	}
	j = -1;
	i = skiplines(all->map);
	while (all->map[i][++j])
		if (!check_arg("02NWES", all->map[i][j]))
			return (-1);
	return (0);
}

int		store_map(t_list **head, t_all *all, int size)
{
	t_list	*tmp;
	int		i;
	int		f;

	i = 0;
	f = 0;
	tmp = *head;
	if (!(all->map = ft_calloc(size + 1, sizeof(char *))))
		return (-1);
	while (tmp && size > 0)
	{
		if (ft_strlen(tmp->content))
		{
			all->map[i++] = ft_strdup(tmp->content);
			size--;
			f = 1;
		}
		if (!ft_strlen(tmp->content) && f == 1)
			print_error("Error: something went wrong");
		free(tmp->content);
		tmp = tmp->next;
	}
	all->map[i] = NULL;
	ft_lstclear(head, &free);
	return (0);
}

int		read_map(int fd, char *line, t_all *all)
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
	if (store_map(&head, all, i) == -1)
		print_error("Error: cannot allocate memory");
	if (check_map(all) == -1)
		print_error("Error: something wrong with map");
	if (parse_map(all) == -1)
		print_error("Error: map is not closed");
	close(fd);
	return (0);
}
