/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:03:29 by maeskhai          #+#    #+#             */
/*   Updated: 2026/01/22 13:14:51 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	ft_len_sep(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	ft_free_arr(char **arr, int index)
{
	while (index > 0)
	{
		index--;
		free(arr[index]);
	}
	free(arr);
}

static char	**ft_spwork(char **arr, char *s, char c, int n_words)
{
	int	i;

	i = 0;
	while (i < n_words)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			arr[i] = ft_substr(s, 0, ft_len_sep(s, c));
			if (arr[i] == NULL)
			{
				ft_free_arr(arr, i);
				return (NULL);
			}
		}
		while (*s && *s != c)
			s++;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split_rgb(char *s, char c)
{
	char	**arr;
	int		n_words;

	if (!s)
		return (NULL);
	n_words = ft_nwords(s, c);
	arr = malloc((n_words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (ft_spwork(arr, s, c, n_words));
}
