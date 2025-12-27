/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:32:44 by sabderra          #+#    #+#             */
/*   Updated: 2025/12/27 11:33:57 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int key_press(int keycode, t_game *g)
{
    if (keycode == KEY_ESC)
        close_game(g);
    if (keycode == KEY_W)
        g->keys.w = 1;
    if (keycode == KEY_S)
        g->keys.s = 1;
    if (keycode == KEY_A)
        g->keys.a = 1;
    if (keycode == KEY_D)
        g->keys.d = 1;
    if (keycode == KEY_LEFT)
        rotate_left(g);
    if (keycode == KEY_RIGHT)
        rotate_right(g);
    return (0);
}

int key_release(int keycode, t_game *g)
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

int is_wall(t_game *g, double x, double y)
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

int close_game(t_game *g)
{
    mlx_destroy_window(g->mlx, g->win);
    exit(0);
    return (0);
}
