/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:32:27 by maeskhai          #+#    #+#             */
/*   Updated: 2026/01/22 15:32:48 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_player(t_data *dt, int *count, int x, int y)
{
	char	c;

	c = dt->map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*count)++;
		dt->player_x = x;
		dt->player_y = y;
		dt->player_dir = c;
		if (*count == 2)
			ft_print_error(
				"Error\nMore than one player found in the map!\n",
				dt->map, NULL);
	}
}

static void	scan_map_for_player(t_data *dt, int *count)
{
	int	y;
	int	x;

	y = 0;
	while (dt->map[y])
	{
		x = 0;
		while (dt->map[y][x])
		{
			check_player(dt, count, x, y);
			x++;
		}
		y++;
	}
}

void	find_single_player(t_data *dt)
{
	int	count;

	count = 0;
	scan_map_for_player(dt, &count);
	if (!dt->map || dt->player_x == -1
		|| dt->player_y == -1 || dt->player_dir == '\0')
		ft_print_error("Error\nNo player found in the map!\n", dt->map, NULL);
}
