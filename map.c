/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:37:40 by keuclide          #+#    #+#             */
/*   Updated: 2021/01/26 16:34:37 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		store_map(t_list **head, t_all *all, int size)
{
	int		i;
	t_list	*tmp;

	if (!(all->map = ft_calloc(size + 1, sizeof(char *))))
		return (-1);
	i = -1;
	tmp = *head;
	while (tmp)
	{
		all->map[++i] = tmp->content;
		tmp = tmp->next;
	}
	all->map[i] = NULL;
	// i = -1;
	// while (all->map[++i])
	// 	ft_putendl_fd(all->map[i], 1);
	ft_lstclear(head, &free);
	return (0);
}

int		read_map(char *str, t_list **head)
{
	char	*line;
	int		fd;

	*head = NULL;
	line = NULL;
	if ((fd = open(str, O_RDONLY)) == -1)
		return (-1);
	while ((get_next_line(fd, &line)) > 0)
		ft_lstadd_back(head, ft_lstnew(line));
	ft_lstadd_back(head, ft_lstnew(line));
	free(line);
	return (0);
}

//-----------------parse-map---------------------

int		check_map(char **line, t_all *all)
{
	char	**args;

	args = ft_split(*line, ' ');
}

int		map(int fd, char **line, t_all *all)
{
	while (get_next_line(fd, line) > 0)
	{
		if (*line[0] != '\0' && (check_map(line, all) == -1))
			return (-1);
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}

//-----------------------------------------------