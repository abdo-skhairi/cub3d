/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:35:00 by maeskhai          #+#    #+#             */
/*   Updated: 2025/12/25 15:25:39 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	ft_print_error(char *s, char **map, char *line)
{
	int	i;

	if (map != NULL)
		ft_free_map(map);
	if (line != NULL)
		free(line);
	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	exit(1);
}
