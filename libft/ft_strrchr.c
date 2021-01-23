/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:40:42 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/05 03:03:13 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ns;
	size_t	i;

	i = 0;
	ns = (char *)s;
	while (ns[i])
		i++;
	if (c == 0)
		return (ns + i);
	while (i > 0)
	{
		i--;
		if (ns[i] == c)
			return (ns + i);
	}
	return (NULL);
}
