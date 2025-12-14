/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:29:32 by maeskhai          #+#    #+#             */
/*   Updated: 2025/11/26 18:01:41 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_var_dt(t_data *dt)
{
	dt->nb_no = 0;
	dt->nb_so = 0;
	dt->nb_we = 0;
	dt->nb_ea = 0;
	dt->nb_f = 0;
	dt->nb_c = 0;
	dt->no = NULL;
	dt->so = NULL;
	dt->we = NULL;
	dt->ea = NULL;
	dt->f_color = NULL;
	dt->c_color = NULL;
	dt->map_line_start = 0;
	dt->f.r = -1;
	dt->f.g = -1;
	dt->f.b = -1;
	dt->c.r = -1;
	dt->c.g = -1;
	dt->c.b = -1;
	dt->map = NULL;
	dt->map_height = 0;
	dt->player_x = -1;
	dt->player_y = -1;
	dt->player_dir = '\0';
	dt->map_line_start = 0;
	dt->fd = 0;
	dt->map_last_line = 0;
}

void	ft_read_fd(char *fd_in, t_data *dt)
{
	char	*line;

	init_var_dt(dt);
	dt->fd = open(fd_in, O_RDONLY);
	if (dt->fd < 0)
		ft_print_error("Eroor\nCan't Open File fd_in!\n", NULL, NULL);
	line = get_next_line(dt->fd);
	if (!line)
		ft_print_error("Error\nEmpty file / Nothing..!\n", NULL, NULL);
	while (line)
	{
		ft_check_line(line, dt);
		// free(line);
		line = get_next_line(dt->fd);
	}
	if (!dt->map || !dt->map[0])
        ft_print_error("Error\nNo map found in file!\n", dt->map, line);
}
