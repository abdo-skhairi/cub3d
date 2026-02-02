/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:50:38 by abdo              #+#    #+#             */
/*   Updated: 2026/02/02 18:48:57 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_game *g, t_ray *r, int x)
{
	r->camera_x = (2.0 * x / (double)g->win_w) - 1.0;
	r->ray_dir_x = g->player.dir_x + g->player.plane_x * r->camera_x;
	r->ray_dir_y = g->player.dir_y + g->player.plane_y * r->camera_x;
	r->map_x = (int)g->player.x;
	r->map_y = (int)g->player.y;
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0 / r->ray_dir_y);
	r->hit = 0;
}

static void	init_step_and_side(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->player.x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - g->player.x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->player.y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - g->player.y) * r->delta_dist_y;
	}
}

static void	perform_dda(t_game *g, t_ray *r)
{
	while (!r->hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_y < 0
			|| r->map_y >= g->map_h
			|| !g->map[r->map_y]
			|| r->map_x >= (int)ft_strlen(g->map[r->map_y]))
			return ;
		if (g->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

static void	draw_column_textured(t_game *g, t_ray *r,
	int x, double perp_dist)
{
	t_texcol	c;

	if (perp_dist <= 0)
		return ;
	init_texture_column(g, r, perp_dist, &c);
	draw_column_pixel(g, r, &c, x);
}

void	draw_scene(t_game *g)
{
	int		x;
	t_ray	r;
	double	perp_dist;

	x = 0;
	while (x < g->win_w)
	{
		init_ray(g, &r, x);
		init_step_and_side(g, &r);
		perform_dda(g, &r);
		if (!r.hit)
		{
			x++;
			continue ;
		}
		perp_dist = get_perp_wall_dist(g, &r);
		draw_column_textured(g, &r, x, perp_dist);
		x++;
	}
}
