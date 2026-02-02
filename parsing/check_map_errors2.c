/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:17:04 by maeskhai          #+#    #+#             */
/*   Updated: 2026/01/22 15:29:27 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_check_bef_aft(int i, int j, t_data *dt)
{
	int	bef_curr;
	int	aft_curr;

	bef_curr = ft_strlen(dt->map[i - 1]);
	aft_curr = ft_strlen(dt->map[i + 1]);
	if (bef_curr <= j || aft_curr <= j)
		return (0);
	return (1);
}

static void	check_first_line(t_data *dt)
{
	int	i;

	i = 0;
	while (dt->map[0][i])
	{
		if (dt->map[0][i] != '1' && dt->map[0][i] != ' ')
			ft_print_error("Error\nfirst line map error!\n", NULL, NULL);
		i++;
	}
}

static void	check_middle_cell(t_data *dt, int i, int j, int len)
{
	if (dt->map[i][0] == '0' || dt->map[i][len - 1] == '0')
		ft_print_error("Error\nmap bounds\n", NULL, NULL);
	if (dt->map[i][j] == '0')
	{
		if (!ft_check_bef_aft(i, j, dt))
			ft_print_error("Error\nMap bounds\n", NULL, NULL);
		if (((i > 0 && i < dt->map_last_line) && (j > 0 && j < len - 1))
			&& (dt->map[i][j - 1] == ' ' || dt->map[i][j + 1] == ' '
				|| dt->map[i - 1][j] == ' ' || dt->map[i + 1][j] == ' '))
			ft_print_error("Error\nMap bounds\n", NULL, NULL);
	}
}

static void	check_middle_lines(t_data *dt)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	while (i < dt->map_last_line)
	{
		len = ft_strlen(dt->map[i]);
		j = 0;
		while (j < len)
		{
			check_middle_cell(dt, i, j, len);
			j++;
		}
		i++;
	}
}

void	ft_check_sides_map(t_data *dt)
{
	int	i;

	dt->map_last_line = 0;
	while (dt->map[dt->map_last_line])
		dt->map_last_line++;
	dt->map_last_line--;
	check_first_line(dt);
	check_middle_lines(dt);
	i = 0;
	while (dt->map[dt->map_last_line][i])
	{
		if (dt->map[dt->map_last_line][i] != '1'
			&& dt->map[dt->map_last_line][i] != ' ')
			ft_print_error("Error\nlast line map error!\n", NULL, NULL);
		i++;
	}
}
