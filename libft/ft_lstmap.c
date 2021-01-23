/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:17:49 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/17 20:46:54 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *begin;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	if ((new = ft_lstnew(f(lst->content))) == NULL)
		return (NULL);
	begin = new;
	lst = lst->next;
	while (lst != NULL)
	{
		if ((new = ft_lstnew(f(lst->content))) == NULL)
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		ft_lstadd_back(&begin, new);
		lst = lst->next;
	}
	return (begin);
}
