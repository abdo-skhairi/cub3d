/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:29:26 by maeskhai          #+#    #+#             */
/*   Updated: 2026/01/17 02:20:24 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_is_empty_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_init_map(char *line, t_data *dt)
{
	char	*merge;
	char	*tmp;
	int		check;

	merge = ft_strdup("");
	check = 0;
	while (line)
	{
		if (!ft_is_empty_line(line) && check == 1)
			ft_print_error("Error\nMap error!\n", NULL, NULL);
		if (ft_is_empty_line(line))
			check = 1;
		tmp = ft_strjoin(merge, line);
		free(line);
		merge = tmp;
		line = get_next_line(dt->fd);
	}
	close(dt->fd);
	dt->map = ft_split(merge, '\n');
	if (merge)
		free(merge);
	dt->map_height = 0;
	while (dt->map && dt->map[dt->map_height])
		dt->map_height++;
	ft_check_map_error(dt);
}
