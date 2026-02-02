/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:33:22 by maeskhai          #+#    #+#             */
/*   Updated: 2026/01/22 15:30:40 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_line_chars(char *line, int *player_count, char **map)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] != '0' && line[j] != '1'
			&& line[j] != 'N' && line[j] != 'S'
			&& line[j] != 'E' && line[j] != 'W'
			&& line[j] != ' ')
			ft_print_error("Error\nInvalid character in map!\n", map, NULL);
		if (line[j] == 'N' || line[j] == 'S'
			|| line[j] == 'E' || line[j] == 'W')
			(*player_count)++;
		j++;
	}
	return (0);
}

void	ft_check_map_chars(t_data *dt)
{
	int	i;
	int	player_count;

	i = 0;
	player_count = 0;
	while (dt->map[i])
	{
		check_line_chars(dt->map[i], &player_count, dt->map);
		i++;
	}
	if (player_count != 1)
		ft_print_error(
			"Error\nMap must contain exactly one player start position!\n",
			dt->map, NULL);
}

void	ft_check_map_error(t_data *dt)
{
	ft_check_map_chars(dt);
	ft_check_sides_map(dt);
	find_single_player(dt);
}
