/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:17:17 by maeskhai          #+#    #+#             */
/*   Updated: 2025/01/28 13:48:03 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **s1, char **s2)
{
	if (s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2)
	{
		free(*s2);
		*s2 = NULL;
	}
}

char	*ft_next(char *next1)
{
	char	*next2;
	int		index;
	int		i;

	i = 0;
	index = 0;
	index = ft_strchr(next1, '\n');
	if (index == -1)
		return (NULL);
	if (next1[index + 1] == 0)
	{
		ft_free(&next1, NULL);
		return (NULL);
	}
	index++;
	next2 = ft_calloc(ft_strlen(next1 + index) + 1, 1);
	if (!next1)
	{
		ft_free(&next1, NULL);
		return (NULL);
	}
	while (next1[index])
		next2[i++] = next1[index++];
	ft_free(&next1, NULL);
	return (next2);
}

char	*ft_new_line(char *next1)
{
	char	*line;
	int		index;

	if (!next1 || !*next1)
		return (NULL);
	index = ft_strchr(next1, '\n');
	if (index == -1)
		return (next1);
	else
	{
		index++;
		line = ft_calloc(index + 1, 1);
		if (!line)
			return (NULL);
	}
	while (index--)
		line[index] = next1[index];
	return (line);
}

void	ft_readjoin(int fd, char **next1)
{
	char	*buff;
	ssize_t	r;

	r = 1;
	buff = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff)
	{
		ft_free(next1, NULL);
		return ;
	}
	while (ft_strchr(buff, '\n') == -1 && r != 0)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			ft_free(next1, NULL);
			break ;
		}
		buff[r] = '\0';
		*next1 = ft_strjoin(*next1, buff);
		if (!*next1)
			break ;
	}
	ft_free(&buff, NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*next1;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_readjoin(fd, &next1);
	if (!next1)
		return (NULL);
	line = ft_new_line(next1);
	if (!line)
	{
		ft_free(&next1, NULL);
		return (NULL);
	}
	next1 = ft_next(next1);
	return (line);
}
