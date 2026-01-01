/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 12:21:12 by sabderra          #+#    #+#             */
/*   Updated: 2026/01/01 21:28:10 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

#define PLAYER_RADIUS   0.25
#define FOV             0.66

static void normalize(double *x, double *y)
{
    double len;

    len = sqrt((*x) * (*x) + (*y) * (*y));
    if (len > 0.0)
    {
        *x /= len;
        *y /= len;
    }
}

void move_forward(t_game *g)
{
    double new_x;
    double new_y;

    new_x = g->player.x
        + g->player.dir_x * (MOVE_SPEED + PLAYER_RADIUS);
    new_y = g->player.y
        + g->player.dir_y * (MOVE_SPEED + PLAYER_RADIUS);

    if (!is_wall(g, new_x, new_y))
    {
        g->player.x += g->player.dir_x * MOVE_SPEED;
        g->player.y += g->player.dir_y * MOVE_SPEED;
    }
}

void move_backward(t_game *g)
{
    double new_x;
    double new_y;

    new_x = g->player.x
        - g->player.dir_x * (MOVE_SPEED + PLAYER_RADIUS);
    new_y = g->player.y
        - g->player.dir_y * (MOVE_SPEED + PLAYER_RADIUS);

    if (!is_wall(g, new_x, new_y))
    {
        g->player.x -= g->player.dir_x * MOVE_SPEED;
        g->player.y -= g->player.dir_y * MOVE_SPEED;
    }
}


void strafe_left(t_game *g)
{
    double new_x;
    double new_y;

    new_x = g->player.x
        - g->player.plane_x * (MOVE_SPEED + PLAYER_RADIUS);
    new_y = g->player.y
        - g->player.plane_y * (MOVE_SPEED + PLAYER_RADIUS);

    if (!is_wall(g, new_x, new_y))
    {
        g->player.x -= g->player.plane_x * MOVE_SPEED;
        g->player.y -= g->player.plane_y * MOVE_SPEED;
    }
}

void strafe_right(t_game *g)
{
    double new_x;
    double new_y;

    new_x = g->player.x
        + g->player.plane_x * (MOVE_SPEED + PLAYER_RADIUS);
    new_y = g->player.y
        + g->player.plane_y * (MOVE_SPEED + PLAYER_RADIUS);

    if (!is_wall(g, new_x, new_y))
    {
        g->player.x += g->player.plane_x * MOVE_SPEED;
        g->player.y += g->player.plane_y * MOVE_SPEED;
    }
}

void rotate_right(t_game *g)
{
    double old_dir_x;

    old_dir_x = g->player.dir_x;
    g->player.dir_x = g->player.dir_x * cos(ROT_SPEED)
        - g->player.dir_y * sin(ROT_SPEED);
    g->player.dir_y = old_dir_x * sin(ROT_SPEED)
        + g->player.dir_y * cos(ROT_SPEED);

    normalize(&g->player.dir_x, &g->player.dir_y);
    g->player.plane_x = -g->player.dir_y * FOV;
    g->player.plane_y =  g->player.dir_x * FOV;
}

void rotate_left(t_game *g)
{
    double old_dir_x;

    old_dir_x = g->player.dir_x;
    g->player.dir_x = g->player.dir_x * cos(-ROT_SPEED)
        - g->player.dir_y * sin(-ROT_SPEED);
    g->player.dir_y = old_dir_x * sin(-ROT_SPEED)
        + g->player.dir_y * cos(-ROT_SPEED);

    normalize(&g->player.dir_x, &g->player.dir_y);
    g->player.plane_x = -g->player.dir_y * FOV;
    g->player.plane_y =  g->player.dir_x * FOV;
}
