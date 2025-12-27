/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 12:21:07 by sabderra          #+#    #+#             */
/*   Updated: 2025/12/27 11:55:32 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

typedef struct s_column
{
	int		draw_start;
	int		draw_end;
	t_img	*tex;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;
}	t_column;

void	init_ray(t_game	*g, t_ray	*r, int x)
{
	r->camera_x = 2 * x / (double)g->win_w - 1;
	r->ray_dir_x = g->player.dir_x + g->player.plane_x * r->camera_x;
	r->ray_dir_y = g->player.dir_y + g->player.plane_y * r->camera_x;
	r->map_x = (int)g->player.x;
	r->map_y = (int)g->player.y;
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1 / r->ray_dir_y);
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
		if (r->map_y < 0 || r->map_x < 0
			|| r->map_y >= g->map_h
			|| !g->map[r->map_y]
			|| r->map_x >= (int)ft_strlen(g->map[r->map_y]))
			return ;
		if (g->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

static void	compute_column_data(t_game *g, t_ray *r, double perp_dist,
								int *draw_start, int *draw_end,
								t_img	**tex, int	*tex_x,
								double *step, double *tex_pos)
{
	int		line_h;
	double	wall_x;

	line_h = (int)(g->win_h / perp_dist);
	*draw_start = -line_h / 2 + g->win_h / 2;
	*draw_end = line_h / 2 + g->win_h / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= g->win_h)
		*draw_end = g->win_h - 1;
	if (r->side == 0)
		wall_x = g->player.y + perp_dist * r->ray_dir_y;
	else
		wall_x = g->player.x + perp_dist * r->ray_dir_x;
	wall_x -= floor(wall_x);
	*tex = select_texture(g, r);
	*tex_x = (int)(wall_x * (*tex)->width);
	if ((r->side == 0 && r->ray_dir_x > 0)
		|| (r->side == 1 && r->ray_dir_y < 0))
		*tex_x = (*tex)->width - *tex_x - 1;
	*step = 1.0 * (*tex)->height / line_h;
	*tex_pos = (*draw_start - g->win_h / 2 + line_h / 2) * (*step);
}

static void	draw_column(t_game *g, t_ray *r,
			int x, double perp_dist)
{
	t_column	col;
	int			tex_y;
	int			color;

	compute_column_data(g, r, perp_dist,
		&col.draw_start, &col.draw_end, &col.tex,
		&col.tex_x, &col.step, &col.tex_pos);
	col.y = 0;
	while (col.y < g->win_h)
	{
		if (col.y < col.draw_start)
			put_pixel(&g->img, x, col.y, g->ceiling_color);
		else if (col.y > col.draw_end)
			put_pixel(&g->img, x, col.y, g->floor_color);
		else
		{
			tex_y = (int)col.tex_pos & (col.tex->height - 1);
			color = get_texture_pixel(col.tex, col.tex_x, tex_y);
			if (r->side == 1)
				color = ((color >> 1) & 0x7F7F7F);
			put_pixel(&g->img, x, col.y, color);
			col.tex_pos += col.step;
		}
		col.y++;
	}
}

void	draw_scene(t_game	*g)
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
		perp_dist = get_perp_wall_dist(g, &r);
		draw_column(g, &r, x, perp_dist);
		x++;
	}
}
