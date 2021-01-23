/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:33:39 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/07 17:19:03 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sour;
	size_t			i;

	i = 0;
	sour = (unsigned char *)s;
	while (i < n)
	{
		if (sour[i] == (unsigned char)c)
			return (sour + i);
		i++;
	}
	return (NULL);
}
