/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:37:40 by keuclide          #+#    #+#             */
/*   Updated: 2021/01/27 19:32:45 by keuclide         ###   ########.fr       */
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
			}
			else
				return (-1);
		}
		if (j == 0)
			return (-1);
	}
	return ((all->flags.p_flag > 1 ||
			!all->flags.p_flag) ? -1 : 0);
}

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
	ft_lstadd_back(&head, ft_lstnew(line));
	while (get_next_line(fd, &line) > 0)
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	if (store_map(&head, all, ft_lstsize(head)) == -1)
		return (print_error("malloc error"));
	if (check_map(all) == -1)
		return (print_error("map error"));
	// free(line);
	close(fd);
	return (0);
}

//-----------------------------------------------