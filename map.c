/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:37:40 by keuclide          #+#    #+#             */
/*   Updated: 2021/01/27 01:16:53 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// int		store_map(t_list **head, t_all *all, int size)
// {
// 	int		i;
// 	t_list	*tmp;

// 	if (!(all->map = ft_calloc(size + 1, sizeof(char *))))
// 		return (-1);
// 	i = -1;
// 	tmp = *head;
// 	while (tmp)
// 	{
// 		all->map[++i] = tmp->content;
// 		tmp = tmp->next;
// 	}
// 	all->map[i] = NULL;
// 	// i = -1;
// 	// while (all->map[++i])
// 	// 	ft_putendl_fd(all->map[i], 1);
// 	ft_lstclear(head, &free);
// 	return (0);
// }

// int		read_map(char *str, t_list **head)
// {
// 	char	*line;
// 	int		fd;

// 	*head = NULL;
// 	line = NULL;
// 	if ((fd = open(str, O_RDONLY)) == -1)
// 		return (-1);
// 	while ((get_next_line(fd, &line)) > 0)
// 		ft_lstadd_back(head, ft_lstnew(line));
// 	ft_lstadd_back(head, ft_lstnew(line));
// 	free(line);
// 	return (0);
// }

//-----------------parse-map---------------------

int		check_args(char *word)
{
	int		i;
	
	i = 0;
	while (word[i])
	{
		if (word[i] == '0' || word[i] == '1' || word[i] == '2' ||
			word[i] == 'N' || word[i] == 'S' || word[i] == 'E' ||
			word[i] == 'W' || word[i] == ' ')
			return (0);
		i++;
	}
	return (-1);
}

int		store_map(t_list **head, t_all *all, int size)
{
	t_list	*tmp;
	int		i;

	i = -1;
	tmp = *head;
	if (!(all->map = ft_calloc(size + 1, sizeof(char *))))
		return (-1);
	while (tmp)
	{
		// if (!check_args(tmp->content))
			all->map[++i] = tmp->content;
		tmp = tmp->next;
	}
	all->map[i] = NULL;
	ft_lstclear(head, &free);
	return (0);
}

int		read_map(int fd, char *line, t_all *all)
{
	t_list	*head;
	int		rt;
	int		s;

	head = NULL;
	while (get_next_line(fd, &line) > 0)
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	free(line);
	s = store_map(&head, all, ft_lstsize(head));
	close(fd);
	return ((s < 0) ? -1 : 0);
}

//-----------------------------------------------