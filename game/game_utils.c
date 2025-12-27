/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:32:44 by sabderra          #+#    #+#             */
/*   Updated: 2025/12/27 13:32:25 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
