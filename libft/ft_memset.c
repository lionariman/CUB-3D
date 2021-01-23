/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:01:41 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/12 15:37:25 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	unsigned char	*w;
	size_t			i;

	i = 0;
	w = (unsigned char *)dest;
	while (i < n)
	{
		*w = (unsigned char)c;
		w++;
		i++;
	}
	return (dest);
}
