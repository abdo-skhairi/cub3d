/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:14:26 by maeskhai          #+#    #+#             */
/*   Updated: 2025/11/24 16:32:08 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_search(char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*str;
	int		i;
	int		j;
	int		size_str;

	if (!s1)
		return (NULL);
	if (!set)
		return (s1);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_search(set, s1[i]))
	{
		i++;
	}
	while (j >= 0 && ft_search(set, s1[j]))
	{
		j--;
	}
	size_str = (j - i) + 1;
	str = ft_substr(s1, i, size_str);
	return (str);
}
