/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 20:35:23 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/17 20:51:14 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**free_maker(char **mem, int i)
{
	while (mem[i] != NULL)
	{
		free(mem[i]);
		i++;
	}
	free(mem);
	return (NULL);
}

static char		*malloc_word(char *mem, char c)
{
	char		*word;
	int			i;

	i = 0;
	while (mem[i] && mem[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (mem[i] && mem[i] != c)
	{
		word[i] = mem[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int		count_words(char *s, char c)
{
	int			i;
	int			x;
	int			counter;

	i = 0;
	x = 0;
	counter = 0;
	while (s[i])
	{
		if (x == 0 && s[i] != c)
		{
			counter++;
			x = 1;
		}
		if (x == 1 && s[i] == c)
			x = 0;
		i++;
	}
	return (counter);
}

static char		**new_split(const char *s, char c, char **mem)
{
	int			j;

	j = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s != c)
		{
			while (*s && *s != c)
			{
				if ((mem[j] = malloc_word((char *)s, c)) == NULL)
					return (free_maker(mem, j));
				while (*s && *s != c)
					s++;
				j++;
			}
		}
		if (*s == '\0')
			break ;
		s++;
	}
	mem[j] = NULL;
	return (mem);
}

char			**ft_split(char const *s, char c)
{
	char		**mem;
	int			j;

	j = 0;
	if (s == NULL)
		return (NULL);
	if ((mem = (char **)malloc(sizeof(char *) *
					(count_words((char *)s, c) + 1))) == NULL)
		return (NULL);
	return (new_split(s, c, mem));
}
