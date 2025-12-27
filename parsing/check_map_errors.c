/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:33:22 by maeskhai          #+#    #+#             */
/*   Updated: 2025/12/25 15:25:27 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    ft_check_map_chars(t_data *dt)
{
	int	i;
	int	j;
	int player_count;

	i = 0;
	player_count = 0;
	while (dt->map[i])
	{
		j = 0;
		while (dt->map[i][j])
		{
			if (dt->map[i][j] != '0' && dt->map[i][j] != '1' &&
				dt->map[i][j] != 'N' && dt->map[i][j] != 'S' &&
				dt->map[i][j] != 'E' && dt->map[i][j] != 'W' &&
				dt->map[i][j] != ' ')
			{
				ft_print_error("Error\nInvalid character in map!\n", dt->map, NULL);
			}
			if (dt->map[i][j] == 'N' || dt->map[i][j] == 'S' ||
				dt->map[i][j] == 'E' || dt->map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		ft_print_error("Error\nMap must contain exactly one player start position!\n", dt->map, NULL);
}

int	ft_check_bef_aft(int i, int j, t_data *dt)
{
	int bef_curr = ft_strlen(dt->map[i - 1]);
	int aft_curr = ft_strlen(dt->map[i + 1]);

	if (bef_curr <= j || aft_curr <= j)
		return (0);
	return (1);
}

void    ft_check_sides_map(t_data *dt)
{
	int	i;
	int	j;
	int	len;

	// hadi line lwli dyalk  --------------------------- abiiiiiiiiiiiii
	dt->map_last_line = 0;
	while (dt->map[dt->map_last_line])
		dt->map_last_line++;
	dt->map_last_line--;

	i = 0;
	while (dt->map[0][i])
	{
		if (dt->map[0][i] != '1' && dt->map[0][i] != ' ')
			ft_print_error("Error\nfirst line map error!\n", NULL, NULL);
		i++;
	}
	// hadi fiha lwst kaml bkolchi dyalo 7ta 0 wach mdwar b 1 ---------------------------
	i = 1;
	while (i < dt->map_last_line)
	{
		j = 0;
		len = ft_strlen(dt->map[i]);
		while (j < len)
		{
			if (dt->map[i][0] == '0' || dt->map[i][len - 1] == '0')
				ft_print_error("Error\nmap bounds\n", NULL, NULL);

			if (dt->map[i][j] == '0')
			{
				if (!ft_check_bef_aft(i, j, dt))
					ft_print_error("Error\nMap bounds\n", NULL, NULL);


				
				if (((i > 0 && i < dt->map_last_line) && (j > 0 && j < len - 1))
						&& (dt->map[i][j - 1] == ' ' || dt->map[i][j + 1] == ' ' || dt->map[i - 1][j] == ' ' || dt->map[i + 1][j] == ' '))
				{
					ft_print_error("Error\nMap bounds\n", NULL, NULL);
				}
			}
			j++;
		}
		i++;
	}
	// hadi line lakhri radito hnaya ---------------------------
	i = 0;
	while (dt->map[dt->map_last_line][i])
	{
		if (dt->map[dt->map_last_line][i] != '1' && dt->map[dt->map_last_line][i] != ' ')
			ft_print_error("Error\nlast line map error!\n", NULL, NULL);
		i++;
	}
}

void	find_single_player(t_data *dt)
{
	int count;
	int y;
	int x;

	count = 0;
	y = 0;
	while (dt->map[y])
	{
		x = 0;
		while (dt->map[y][x])
		{
			char c = dt->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				++count;
				dt->player_x = x;
				dt->player_y = y;
				dt->player_dir = c;
				if (count == 2)
					ft_print_error("Error\nMore than one player found in the map!\n", dt->map, NULL);
			}
			x++;
		}
		y++;
	}
	if (!dt->map || dt->player_x == -1 || dt->player_y == -1 || dt->player_dir == '\0')
		ft_print_error("Error\nNo player found in the map!\n", dt->map, NULL);
}

void	ft_check_map_error(t_data *dt)
{
	ft_check_map_chars(dt);
	ft_check_sides_map(dt);
	find_single_player(dt);
}
