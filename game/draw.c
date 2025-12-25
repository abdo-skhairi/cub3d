/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 12:21:07 by sabderra          #+#    #+#             */
/*   Updated: 2025/12/25 12:44:55 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub3d.h"

static void init_ray(t_game *g, t_ray *r, int x)
{
    r->camera_x = 2 * x / (double)g->win_w - 1;
    r->ray_dir_x = g->player.dir_x + g->player.plane_x * r->camera_x;
    r->ray_dir_y = g->player.dir_y + g->player.plane_y * r->camera_x;
    r->map_x = (int)g->player.x;
    r->map_y = (int)g->player.y;
    r->delta_dist_x = (r->ray_dir_x == 0) ? 1e30 : fabs(1 / r->ray_dir_x);
    r->delta_dist_y = (r->ray_dir_y == 0) ? 1e30 : fabs(1 / r->ray_dir_y);
    r->hit = 0;
}

static void init_step_and_side(t_game *g, t_ray *r)
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

static void perform_dda(t_game *g, t_ray *r)
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
            return;
        if (g->map[r->map_y][r->map_x] == '1')
            r->hit = 1;
    }
}

static void draw_column(t_game *g, t_ray *r, int x, double perp_dist)
{
    int     line_h;
    int     draw_start;
    int     draw_end;
    double  wall_x;
    t_img   *tex;
    int     tex_x;
    double  step;
    double  tex_pos;
    int     y;

    line_h = (int)(g->win_h / perp_dist);
    draw_start = -line_h / 2 + g->win_h / 2;
    draw_end = line_h / 2 + g->win_h / 2;
    if (draw_start < 0) draw_start = 0;
    if (draw_end >= g->win_h) draw_end = g->win_h - 1;

    if (r->side == 0)
        wall_x = g->player.y + perp_dist * r->ray_dir_y;
    else
        wall_x = g->player.x + perp_dist * r->ray_dir_x;
    wall_x -= floor(wall_x);

    tex = select_texture(g, r);
    tex_x = (int)(wall_x * tex->width);
    if ((r->side == 0 && r->ray_dir_x > 0)
        || (r->side == 1 && r->ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;

    step = 1.0 * tex->height / line_h;
    tex_pos = (draw_start - g->win_h / 2 + line_h / 2) * step;

    y = 0;
    while (y < g->win_h)
    {
        if (y < draw_start)
            put_pixel(&g->img, x, y, g->ceiling_color);
        else if (y > draw_end)
            put_pixel(&g->img, x, y, g->floor_color);
        else
        {
            int tex_y = (int)tex_pos & (tex->height - 1);
            int color = get_texture_pixel(tex, tex_x, tex_y);
            if (r->side == 1)
                color = ((color >> 1) & 0x7F7F7F);
            put_pixel(&g->img, x, y, color);
            tex_pos += step;
        }
        y++;
    }
}

void draw_scene(t_game *g)
{
    int     x;
    t_ray   r;
    double  perp_dist;

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
