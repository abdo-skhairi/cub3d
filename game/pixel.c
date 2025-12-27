/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:32:17 by sabderra          #+#    #+#             */
/*   Updated: 2025/12/26 18:32:19 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x >= 1024 || y >= 768)
        return;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

int get_texture_pixel(t_img *texture, int x, int y)
{
    char *dst;

    if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
        return (0);
    dst = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
    return (*(unsigned int *)dst);
}

void load_texture(t_game *g, t_img *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(
        g->mlx, path, &texture->width, &texture->height);
    if (!texture->img)
        exit(1);
    texture->addr = mlx_get_data_addr(
        texture->img, &texture->bpp,
        &texture->line_len, &texture->endian);
}

double get_perp_wall_dist(t_game *g, t_ray *r)
{
    double dist;

    if (r->side == 0)
        dist = (r->map_x - g->player.x + (1 - r->step_x) / 2) / r->ray_dir_x;
    else
        dist = (r->map_y - g->player.y + (1 - r->step_y) / 2) / r->ray_dir_y;
    if (dist <= 0)
        dist = 1e-6;
    return (dist);
}

t_img *select_texture(t_game *g, t_ray *r)
{
    if (r->side == 0)
        return (r->ray_dir_x > 0 ? &g->tex_ea : &g->tex_we);
    return (r->ray_dir_y > 0 ? &g->tex_so : &g->tex_no);
}
