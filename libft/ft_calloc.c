/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:52:43 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/09 13:36:04 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*memory;
	int		i;

	i = 0;
	memory = (char *)malloc(count * size);
	if (NULL == memory)
		return (NULL);
	ft_bzero(memory, count * size);
	return ((void *)memory);
}
