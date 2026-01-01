/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 12:21:12 by sabderra          #+#    #+#             */
/*   Updated: 2026/01/01 19:49:39 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

#define PLAYER_RADIUS   0.25
#define FOV             0.66

static int check_collision_circle(t_game *g, double x, double y)
{
    double angle;
    double check_x;
    double check_y;
    int i;

    if (is_wall(g, x, y))
        return (1);
    i = 0;
    while (i < 8)
    {
        angle = i * M_PI / 4.0;
        check_x = x + cos(angle) * PLAYER_RADIUS;
        check_y = y + sin(angle) * PLAYER_RADIUS;
        if (is_wall(g, check_x, check_y))
            return (1);
        i++;
    }
    return (0);
}

static void move_with_slide(t_game *g, double dx, double dy)
{
    double new_x;
    double new_y;

    new_x = g->player.x + dx;
    new_y = g->player.y + dy;
    if (!check_collision_circle(g, new_x, new_y))
    {
        g->player.x = new_x;
        g->player.y = new_y;
    }
    else if (!check_collision_circle(g, new_x, g->player.y))
    {
        g->player.x = new_x;
    }
    else if (!check_collision_circle(g, g->player.x, new_y))
    {
        g->player.y = new_y;
    }
}

void move_forward(t_game *g)
{
    double dx;
    double dy;

    dx = g->player.dir_x * MOVE_SPEED;
    dy = g->player.dir_y * MOVE_SPEED;
    move_with_slide(g, dx, dy);
}

void move_backward(t_game *g)
{
    double dx;
    double dy;

    dx = -g->player.dir_x * MOVE_SPEED;
    dy = -g->player.dir_y * MOVE_SPEED;
    move_with_slide(g, dx, dy);
}

void strafe_left(t_game *g)
{
    double dx;
    double dy;

    dx = -g->player.plane_x * MOVE_SPEED;
    dy = -g->player.plane_y * MOVE_SPEED;
    move_with_slide(g, dx, dy);
}

void strafe_right(t_game *g)
{
    double dx;
    double dy;

    dx = g->player.plane_x * MOVE_SPEED;
    dy = g->player.plane_y * MOVE_SPEED;
    move_with_slide(g, dx, dy);
}

void rotate_right(t_game *g)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = g->player.dir_x;
    old_plane_x = g->player.plane_x;
    g->player.dir_x = g->player.dir_x * cos(ROT_SPEED)
        - g->player.dir_y * sin(ROT_SPEED);
    g->player.dir_y = old_dir_x * sin(ROT_SPEED)
        + g->player.dir_y * cos(ROT_SPEED);
    g->player.plane_x = g->player.plane_x * cos(ROT_SPEED)
        - g->player.plane_y * sin(ROT_SPEED);
    g->player.plane_y = old_plane_x * sin(ROT_SPEED)
        + g->player.plane_y * cos(ROT_SPEED);
    if (check_collision_circle(g, g->player.x, g->player.y))
    {
        int pushed = 0;
        double push_dist = 0.1;
        
        if (!check_collision_circle(g, g->player.x + push_dist, g->player.y))
        {
            g->player.x += push_dist;
            pushed = 1;
        }
        else if (!check_collision_circle(g, g->player.x - push_dist, g->player.y))
        {
            g->player.x -= push_dist;
            pushed = 1;
        }
        else if (!check_collision_circle(g, g->player.x, g->player.y + push_dist))
        {
            g->player.y += push_dist;
            pushed = 1;
        }
        else if (!check_collision_circle(g, g->player.x, g->player.y - push_dist))
        {
            g->player.y -= push_dist;
            pushed = 1;
        }
        (void)pushed;
    }
}

void rotate_left(t_game *g)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = g->player.dir_x;
    old_plane_x = g->player.plane_x;
    g->player.dir_x = g->player.dir_x * cos(-ROT_SPEED)
        - g->player.dir_y * sin(-ROT_SPEED);
    g->player.dir_y = old_dir_x * sin(-ROT_SPEED)
        + g->player.dir_y * cos(-ROT_SPEED);
    g->player.plane_x = g->player.plane_x * cos(-ROT_SPEED)
        - g->player.plane_y * sin(-ROT_SPEED);
    g->player.plane_y = old_plane_x * sin(-ROT_SPEED)
        + g->player.plane_y * cos(-ROT_SPEED);
    if (check_collision_circle(g, g->player.x, g->player.y))
    {
        int pushed = 0;
        double push_dist = 0.1;
        
        if (!check_collision_circle(g, g->player.x + push_dist, g->player.y))
        {
            g->player.x += push_dist;
            pushed = 1;
        }
        else if (!check_collision_circle(g, g->player.x - push_dist, g->player.y))
        {
            g->player.x -= push_dist;
            pushed = 1;
        }
        else if (!check_collision_circle(g, g->player.x, g->player.y + push_dist))
        {
            g->player.y += push_dist;
            pushed = 1;
        }
        else if (!check_collision_circle(g, g->player.x, g->player.y - push_dist))
        {
            g->player.y -= push_dist;
            pushed = 1;
        }
        (void)pushed;
    }
}