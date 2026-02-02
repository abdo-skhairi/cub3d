/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 12:25:43 by sabderra          #+#    #+#             */
/*   Updated: 2026/02/02 19:12:19 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_window_and_map_and_keys(t_game *g, t_data *dt)
{
	g->win_w = 1024;
	g->win_h = 678;
	g->map = dt->map;
	g->map_h = dt->map_height;
	g->keys.w = 0;
	g->keys.s = 0;
	g->keys.a = 0;
	g->keys.d = 0;
}

static void	init_player_position_direction(t_game *g, t_data *dt)
{
	g->player.x = dt->player_x + 0.5;
	g->player.y = dt->player_y + 0.5;
	g->player.dir_x = 0;
	g->player.dir_y = 0;
	if (dt->player_dir == 'N')
		g->player.dir_y = -1;
	if (dt->player_dir == 'S')
		g->player.dir_y = 1;
	if (dt->player_dir == 'E')
		g->player.dir_x = 1;
	if (dt->player_dir == 'W')
		g->player.dir_x = -1;
}

static void	init_player_plane(t_game *g, t_data *dt)
{
	g->player.plane_x = 0;
	g->player.plane_y = 0;
	if (dt->player_dir == 'N')
		g->player.plane_x = 0.66;
	if (dt->player_dir == 'S')
		g->player.plane_x = -0.66;
	if (dt->player_dir == 'E')
		g->player.plane_y = 0.66;
	if (dt->player_dir == 'W')
		g->player.plane_y = -0.66;
}

static void	init_window_and_img(t_game *g, t_data *dt)
{
	if (dt->no)
		free(dt->no);
	if (dt->so)
		free(dt->so);
	if (dt->we)
		free(dt->we);
	if (dt->ea)
		free(dt->ea);
	if (dt->f_color)
		free(dt->f_color);
	if (dt->c_color)
		free(dt->c_color);
	g->win = mlx_new_window(g->mlx, g->win_w, g->win_h, "cub3D");
	g->img.img = mlx_new_image(g->mlx, g->win_w, g->win_h);
	g->img.width = g->win_w;
	g->img.height = g->win_h;
	g->img.addr = mlx_get_data_addr(g->img.img,
			&g->img.bpp, &g->img.line_len, &g->img.endian);
}

void	init_game(t_game *g, t_data *dt)
{
	init_window_and_map_and_keys(g, dt);
	init_player_position_direction(g, dt);
	init_player_plane(g, dt);
	init_colors(g, dt);
	init_textures(g, dt);
	init_window_and_img(g, dt);
}
