/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 22:43:40 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/12 18:03:22 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *ptr;
	t_list *sav;

	sav = *lst;
	while (sav != NULL)
	{
		ptr = sav->next;
		del(sav);
		sav = ptr;
	}
	*lst = NULL;
}
