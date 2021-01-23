/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:37:04 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/17 20:52:13 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*d;
	char	*s;
	size_t	i;
	size_t	o;

	i = 0;
	d = (char *)haystack;
	s = (char *)needle;
	if (!(*s))
		return ((char *)d);
	if (len == 0)
		return (0);
	while (d[i] != '\0' && i < len)
	{
		o = 0;
		while (d[i + o] == s[o] && i + o < len && s[o] != '\0')
			o++;
		if (s[o] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
