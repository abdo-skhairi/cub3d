/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:32:44 by sabderra          #+#    #+#             */
/*   Updated: 2026/02/02 18:56:47 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
		close_game(g);
	if (keycode == KEY_LEFT)
		rotate_left(g);
	if (keycode == KEY_RIGHT)
		rotate_right(g);
	if (keycode == KEY_W)
		g->keys.w = 1;
	if (keycode == KEY_S)
		g->keys.s = 1;
	if (keycode == KEY_A)
		g->keys.a = 1;
	if (keycode == KEY_D)
		g->keys.d = 1;
	return (0);
}

int	key_release(int keycode, t_game *g)
{
	if (keycode == KEY_W)
		g->keys.w = 0;
	if (keycode == KEY_S)
		g->keys.s = 0;
	if (keycode == KEY_A)
		g->keys.a = 0;
	if (keycode == KEY_D)
		g->keys.d = 0;
	return (0);
}

int	is_wall(t_game *g, double x, double y)
{
	if (x < 0 || y < 0)
		return (1);
	if ((int)y >= g->map_h)
		return (1);
	if (!g->map[(int)y])
		return (1);
	if ((int)x >= (int)ft_strlen(g->map[(int)y]))
		return (1);
	if (g->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

double	get_perp_wall_dist(t_game *g, t_ray *r)
{
	double	dist;

	if (r->side == 0)
		dist = (r->map_x - g->player.x
				+ (1 - r->step_x) / 2) / r->ray_dir_x;
	else
		dist = (r->map_y - g->player.y
				+ (1 - r->step_y) / 2) / r->ray_dir_y;
	if (dist <= 0)
		dist = 1e-6;
	return (dist);
}

void	init_texture_column(t_game *g, t_ray *r,
	double perp_dist, t_texcol *c)
{
	int		line_h;
	double	wall_x;

	line_h = (int)(g->win_h / perp_dist);
	c->draw_start = (-(line_h / 2)) + (g->win_h / 2);
	c->draw_end = line_h / 2 + g->win_h / 2;
	if (c->draw_start < 0)
		c->draw_start = 0;
	if (c->draw_end >= g->win_h)
		c->draw_end = g->win_h - 1;
	if (r->side == 0)
		wall_x = g->player.y + (perp_dist * r->ray_dir_y);
	else
		wall_x = g->player.x + (perp_dist * r->ray_dir_x);
	wall_x -= floor(wall_x);
	c->tex = select_texture(g, r);
	c->tex_x = (int)(wall_x * c->tex->width);
	if ((r->side == 0 && r->ray_dir_x > 0)
		|| (r->side == 1 && r->ray_dir_y < 0))
		c->tex_x = c->tex->width - c->tex_x - 1;
	c->step = (double)c->tex->height / line_h;
	c->tex_pos = (c->draw_start - (g->win_h / 2) + line_h / 2) * c->step;
}
