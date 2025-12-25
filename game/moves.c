/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 12:21:12 by sabderra          #+#    #+#             */
/*   Updated: 2025/12/25 12:39:51 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub3d.h"

void move_forward(t_game *g)
{
    double nx = g->player.x + g->player.dir_x * MOVE_SPEED;
    double ny = g->player.y + g->player.dir_y * MOVE_SPEED;

    if (!is_wall(g, nx, g->player.y))
        g->player.x = nx;
    if (!is_wall(g, g->player.x, ny))
        g->player.y = ny;
}

void move_backward(t_game *g)
{
    double nx = g->player.x - g->player.dir_x * MOVE_SPEED;
    double ny = g->player.y - g->player.dir_y * MOVE_SPEED;

    if (!is_wall(g, nx, g->player.y))
        g->player.x = nx;
    if (!is_wall(g, g->player.x, ny))
        g->player.y = ny;
}

void strafe_left(t_game *g)
{
    double nx = g->player.x - g->player.plane_x * MOVE_SPEED;
    double ny = g->player.y - g->player.plane_y * MOVE_SPEED;

    if (!is_wall(g, nx, g->player.y))
        g->player.x = nx;
    if (!is_wall(g, g->player.x, ny))
        g->player.y = ny;
}

void strafe_right(t_game *g)
{
    double nx = g->player.x + g->player.plane_x * MOVE_SPEED;
    double ny = g->player.y + g->player.plane_y * MOVE_SPEED;

    if (!is_wall(g, nx, g->player.y))
        g->player.x = nx;
    if (!is_wall(g, g->player.x, ny))
        g->player.y = ny;
}

void rotate_left(t_game *g)
{
    double old_dir_x = g->player.dir_x;
    double old_plane_x = g->player.plane_x;

    g->player.dir_x = g->player.dir_x * cos(ROT_SPEED)
        - g->player.dir_y * sin(ROT_SPEED);
    g->player.dir_y = old_dir_x * sin(ROT_SPEED)
        + g->player.dir_y * cos(ROT_SPEED);
    g->player.plane_x = g->player.plane_x * cos(ROT_SPEED)
        - g->player.plane_y * sin(ROT_SPEED);
    g->player.plane_y = old_plane_x * sin(ROT_SPEED)
        + g->player.plane_y * cos(ROT_SPEED);
}

void rotate_right(t_game *g)
{
    double old_dir_x = g->player.dir_x;
    double old_plane_x = g->player.plane_x;

    g->player.dir_x = g->player.dir_x * cos(-ROT_SPEED)
        - g->player.dir_y * sin(-ROT_SPEED);
    g->player.dir_y = old_dir_x * sin(-ROT_SPEED)
        + g->player.dir_y * cos(-ROT_SPEED);
    g->player.plane_x = g->player.plane_x * cos(-ROT_SPEED)
        - g->player.plane_y * sin(-ROT_SPEED);
    g->player.plane_y = old_plane_x * sin(-ROT_SPEED)
        + g->player.plane_y * cos(-ROT_SPEED);
}
