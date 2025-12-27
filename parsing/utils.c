/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:16:20 by maeskhai          #+#    #+#             */
/*   Updated: 2025/12/25 15:25:51 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup_2(char *s1)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = (int)ft_strlen(s1);
	str = malloc(size + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		if (s1[i] == '\n')
			break ;
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
