/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:19:11 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/17 21:32:51 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(const char *s1, const char *set)
{
	char	*mem;
	int		start;
	int		end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	end = ft_strlen(s1);
	while (end > 0 && ft_strchr(set, s1[end]))
		end--;
	if (end == 0)
	{
		mem = (ft_substr("", 0, 1));
		return (mem);
	}
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	mem = (ft_substr((char *)s1, start, end - start + 1));
	return (mem);
}
