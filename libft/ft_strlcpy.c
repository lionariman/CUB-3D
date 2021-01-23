/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:48:00 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/09 18:26:54 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*d;
	char	*s;
	size_t	i;

	i = 0;
	s = (char *)src;
	d = (char *)dst;
	if (!d || !s)
		return (0);
	if (dstsize != 0)
	{
		while (s[i] && i < (dstsize - 1))
		{
			d[i] = s[i];
			i++;
		}
		d[i] = '\0';
	}
	i = 0;
	while (s[i])
		i++;
	return (i);
}
