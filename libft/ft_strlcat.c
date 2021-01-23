/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:20:26 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/09 18:17:17 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	x;
	size_t	s;

	i = 0;
	x = 0;
	s = 0;
	while (src[s])
		s++;
	while (dst[i] && i < dstsize)
		i++;
	if (i == dstsize)
		return (s + i);
	while (src[x] && i + x < dstsize - 1)
	{
		dst[i + x] = src[x];
		x++;
	}
	dst[i + x] = '\0';
	return (i + s);
}
