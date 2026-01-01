/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:32:44 by sabderra          #+#    #+#             */
/*   Updated: 2026/01/02 00:03:53 by abdo             ###   ########.fr       */
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

void free_game_resources(t_game *g)
{
    if (!g)
        return ;
    if (g->img.img)
        mlx_destroy_image(g->mlx, g->img.img);
    if (g->tex_no.img)
        mlx_destroy_image(g->mlx, g->tex_no.img);
    if (g->tex_so.img)
        mlx_destroy_image(g->mlx, g->tex_so.img);
    if (g->tex_we.img)
        mlx_destroy_image(g->mlx, g->tex_we.img);
    if (g->tex_ea.img)
        mlx_destroy_image(g->mlx, g->tex_ea.img);
    if (g->win)
        mlx_destroy_window(g->mlx, g->win);
    if (g->mlx)
    {
        mlx_destroy_display(g->mlx);
        free(g->mlx);
        g->mlx = NULL;
    }
    if (g->map)
        ft_free_map(g->map);
}

int close_game(t_game *g)
{
    free_game_resources(g);
    exit(0);
    return (0);
}
