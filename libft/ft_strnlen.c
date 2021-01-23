/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:41:36 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/03 23:09:21 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	unsigned char	*s1;
	int				i;

	i = 0;
	s1 = (unsigned char *)s;
	while (s1[i])
	{
		if (i != (int)maxlen)
			i++;
		else
			return (0);
	}
	return (0);
}
