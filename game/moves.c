/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 12:21:12 by sabderra          #+#    #+#             */
/*   Updated: 2025/12/28 17:06:56 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define PLAYER_RADIUS   0.25
#define ROT_CHECK_DIST  0.35

void move_forward(t_game *g)
{
    double dx;
    double dy;

    dx = g->player.dir_x * MOVE_SPEED;
    dy = g->player.dir_y * MOVE_SPEED;
    if (!is_wall(g,
            g->player.x + dx + g->player.dir_x * PLAYER_RADIUS,
            g->player.y))
        g->player.x += dx;
    if (!is_wall(g,
            g->player.x,
            g->player.y + dy + g->player.dir_y * PLAYER_RADIUS))
        g->player.y += dy;
}

void move_backward(t_game *g)
{
    double dx;
    double dy;

    dx = g->player.dir_x * MOVE_SPEED;
    dy = g->player.dir_y * MOVE_SPEED;
    if (!is_wall(g,
            g->player.x - dx - g->player.dir_x * PLAYER_RADIUS,
            g->player.y))
        g->player.x -= dx;
    if (!is_wall(g,
            g->player.x,
            g->player.y - dy - g->player.dir_y * PLAYER_RADIUS))
        g->player.y -= dy;
}

void strafe_left(t_game *g)
{
    double dx;
    double dy;

    dx = g->player.plane_x * MOVE_SPEED;
    dy = g->player.plane_y * MOVE_SPEED;
    if (!is_wall(g,
            g->player.x - dx - g->player.plane_x * PLAYER_RADIUS,
            g->player.y))
        g->player.x -= dx;
    if (!is_wall(g,
            g->player.x,
            g->player.y - dy - g->player.plane_y * PLAYER_RADIUS))
        g->player.y -= dy;
}

void strafe_right(t_game *g)
{
    double dx;
    double dy;

    dx = g->player.plane_x * MOVE_SPEED;
    dy = g->player.plane_y * MOVE_SPEED;
    if (!is_wall(g,
            g->player.x + dx + g->player.plane_x * PLAYER_RADIUS,
            g->player.y))
        g->player.x += dx;
    if (!is_wall(g,
            g->player.x,
            g->player.y + dy + g->player.plane_y * PLAYER_RADIUS))
        g->player.y += dy;
}

void rotate_right(t_game *g)
{
    double new_dir_x;
    double new_dir_y;
    double old_dir_x;
    double old_plane_x;

    (void)old_dir_x;
    new_dir_x = g->player.dir_x * cos(ROT_SPEED)
        - g->player.dir_y * sin(ROT_SPEED);
    new_dir_y = g->player.dir_x * sin(ROT_SPEED)
        + g->player.dir_y * cos(ROT_SPEED);
    if (is_wall(g,
            g->player.x + new_dir_x * ROT_CHECK_DIST,
            g->player.y + new_dir_y * ROT_CHECK_DIST))
        return ;
    old_dir_x = g->player.dir_x;
    old_plane_x = g->player.plane_x;
    g->player.dir_x = new_dir_x;
    g->player.dir_y = new_dir_y;
    g->player.plane_x = g->player.plane_x * cos(ROT_SPEED)
        - g->player.plane_y * sin(ROT_SPEED);
    g->player.plane_y = old_plane_x * sin(ROT_SPEED)
        + g->player.plane_y * cos(ROT_SPEED);
}

void rotate_left(t_game *g)
{
    double new_dir_x;
    double new_dir_y;
    double old_dir_x;
    double old_plane_x;

    (void)old_dir_x;
    new_dir_x = g->player.dir_x * cos(-ROT_SPEED)
        - g->player.dir_y * sin(-ROT_SPEED);
    new_dir_y = g->player.dir_x * sin(-ROT_SPEED)
        + g->player.dir_y * cos(-ROT_SPEED);
    if (is_wall(g,
            g->player.x + new_dir_x * ROT_CHECK_DIST,
            g->player.y + new_dir_y * ROT_CHECK_DIST))
        return ;
    old_dir_x = g->player.dir_x;
    old_plane_x = g->player.plane_x;
    g->player.dir_x = new_dir_x;
    g->player.dir_y = new_dir_y;
    g->player.plane_x = g->player.plane_x * cos(-ROT_SPEED)
        - g->player.plane_y * sin(-ROT_SPEED);
    g->player.plane_y = old_plane_x * sin(-ROT_SPEED)
        + g->player.plane_y * cos(-ROT_SPEED);
}
