/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:14:17 by maeskhai          #+#    #+#             */
/*   Updated: 2026/01/17 00:49:58 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**my_free(char **tmp, int j)
{
	while (j--)
	{
		free(tmp[j]);
	}
	free(tmp);
	return (NULL);
}

static char	**cp(char **tmp, char *s, char c, int count_wd)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < count_wd)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		tmp[j] = ft_substr(s, start, i - start);
		if (!tmp[j])
			return (my_free(tmp, j));
		j++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char	**ft_split(char *s, char c)
{
	int		count_wd;
	char	**tmp;

	if (!s)
		return (NULL);
	count_wd = count_words(s, c);
	tmp = (char **)malloc(sizeof(char *) * (count_wd + 1));
	if (!tmp)
		return (NULL);
	return (cp(tmp, s, c, count_wd));
}
