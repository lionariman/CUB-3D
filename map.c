/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:37:40 by keuclide          #+#    #+#             */
/*   Updated: 2021/01/28 15:24:07 by keuclide         ###   ########.fr       */
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

void	player_pos(t_all *all, int i, int j)
{
	all->plr.x = j;
	all->plr.y = i;
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

//---------------------------<parse-map>------------------------------

int		skiplines(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
		i++;
	return (i - 1);
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

//---------------------------<parse-map>------------------------------

int		store_map(t_list **head, t_all *all, int size)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *head;
	if (!(all->map = ft_calloc(size + 1, sizeof(char *))))
		return (-1);
	while (tmp)
	{
		all->map[i++] = ft_strdup(tmp->content);
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

	head = NULL;
	line[0] != '\0' ? ft_lstadd_back(&head, ft_lstnew(line)) : free(line);
	while (get_next_line(fd, &line) > 0)
		line[0] != '\0' ? ft_lstadd_back(&head, ft_lstnew(line)) : free(line);
	line[0] != '\0' ? ft_lstadd_back(&head, ft_lstnew(line)) : free(line);
	if (store_map(&head, all, ft_lstsize(head)) == -1)
		return (print_error("malloc error"));
	if (check_map(all) == -1)
		return (print_error("map error"));
	if (parse_map(all) == -1)
		return (print_error("map is not closed"));
	close(fd);
	return (0);
}
