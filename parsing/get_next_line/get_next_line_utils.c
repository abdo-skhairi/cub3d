/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:17:20 by maeskhai          #+#    #+#             */
/*   Updated: 2025/11/24 15:46:50 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	bytes;
	size_t	i;
	char	*p;

	i = 0;
	bytes = count * size;
	if (size && bytes / size != count)
		return (NULL);
	p = malloc(bytes);
	if (!p)
		return (NULL);
	while (i < bytes)
	{
		*(p + i) = 0;
		i++;
	}
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		join_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!*s2)
		return (s1);
	join_len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc((join_len + 1), 1);
	if (!str)
	{
		ft_free(&s1, NULL);
		return (NULL);
	}
	while (s1 && s1[i])
		str[i++] = s1[j++];
	ft_free(&s1, NULL);
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	return (str);
}

int	ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup(char *s1)
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
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
