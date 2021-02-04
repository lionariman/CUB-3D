/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:37:40 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/04 06:39:57 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_arg(char *s, char c)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (0);
	return (-1);
}

int		skiplines(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
		i++;
	return (i - 1);
}

void	player_pos(t_all *all, int i, int j)
{
	all->plr.posX = j;
	all->plr.posY = i;
	if (all->map[i][j] == 'N')
	{
		all->plr.dirX = 0;
		all->plr.dirY = 1;
		all->plane.x = 0;
		all->plane.y = 0.66;
	}
	else if (all->map[i][j] == 'W')
	{
		all->plr.dirX = -1;
		all->plr.dirY = 0;
		all->plane.x = -0.66;
		all->plane.y = 0;
	}
	else if (all->map[i][j] == 'E')
	{
		all->plr.dirX = 0;
		all->plr.dirY= -1;
		all->plane.x = 0;
		all->plane.y = -0.66;
	}
	else if (all->map[i][j] == 'S')
	{
		all->plr.dirX = 1;
		all->plr.dirY = 0;
		all->plane.x = 0.66;
		all->plane.y = 0;
	}
}

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
				(!check_arg("2", all->map[i][j])) ? (all->flags.s_flag++) : 0;
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
			return (print_error("error"));
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
		return (print_error("malloc error"));
	if (check_map(all) == -1)
		return (print_error("map error"));
	if (parse_map(all) == -1)
		return (print_error("error: map is not closed"));
	close(fd);
	return (0);
}
