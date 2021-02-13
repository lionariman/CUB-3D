/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 20:17:04 by keuclide          #+#    #+#             */
/*   Updated: 2021/02/13 12:02:30 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char		*malloc_word(char *mem, char *set)
{
	char		*word;
	int			i;

	i = 0;
	while (!isset(set, mem[i]))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (mem[i] && !isset(set, mem[i]))
	{
		word[i] = mem[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int		count_words(char *s, char *set, t_spl *l)
{
	int			i;
	int			counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		if (l->f == 0 && !isset(set, s[i]))
		{
			counter++;
			l->f = 1;
		}
		if (l->f == 1 && isset(set, s[i]))
			l->f = 0;
		i++;
	}
	return (counter);
}

static char		**spls(char *s, char *set, t_spl *l)
{
	while (*s)
	{
		if (!isset(set, *s))
		{
			if (!(l->mem[l->j] = malloc_word(s, set)))
				return (freesher(l->mem));
			while (*s && !isset(set, *s))
				s++;
			l->j++;
		}
		if (*s == '\0')
			break ;
		s++;
	}
	l->mem[l->j] = NULL;
	return (l->mem);
}

char			**splitset(const char *s, const char *set)
{
	t_spl l;

	init_l(&l);
	if (!(l.mem = (char **)malloc(sizeof(char *) *
		(count_words((char *)s, (char *)set, &l) + 1))))
		return (NULL);
	return (spls((char *)s, (char *)set, &l));
}
