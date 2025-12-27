/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 12:25:43 by sabderra          #+#    #+#             */
/*   Updated: 2025/12/26 18:25:56 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void init_window_and_map(t_game *g, t_data *dt)
{
    g->win_w = 1024;
    g->win_h = 768;
    g->map = dt->map;
    g->map_h = dt->map_height;
}

static void init_keys(t_game *g)
{
    g->keys.w = 0;
    g->keys.s = 0;
    g->keys.a = 0;
    g->keys.d = 0;
}

static void init_player__position_direction(t_game *g, t_data *dt)
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

static void init_player_plane(t_game *g, t_data *dt)
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

static void init_colors(t_game *g, t_data *dt)
{
    g->ceiling_color = (dt->c.r << 16) | (dt->c.g << 8) | dt->c.b;
    g->floor_color = (dt->f.r << 16) | (dt->f.g << 8) | dt->f.b;
}

static void init_mlx(t_game *g, t_data *dt)
{
    g->mlx = mlx_init();
    load_texture(g, &g->tex_no, dt->no);
    load_texture(g, &g->tex_so, dt->so);
    load_texture(g, &g->tex_we, dt->we);
    load_texture(g, &g->tex_ea, dt->ea);
    g->win = mlx_new_window(g->mlx, g->win_w, g->win_h, "cub3D");
    g->img.img = mlx_new_image(g->mlx, g->win_w, g->win_h);
    g->img.addr = mlx_get_data_addr(
        g->img.img,
        &g->img.bpp,
        &g->img.line_len,
        &g->img.endian
    );
}

void init_game(t_game *g, t_data *dt)
{
    init_window_and_map(g, dt);
    init_keys(g);
    init_player__position_direction(g, dt);
    init_player_plane(g, dt);
    init_colors(g, dt);
    init_mlx(g, dt);
}
