/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:41:59 by abdo              #+#    #+#             */
/*   Updated: 2026/02/02 18:57:45 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_collision_circle(t_game *g, double x, double y)
{
	static const double	angles[8] = {
		0,
		PI / 4,
		PI / 2,
		3 * PI / 4,
		PI,
		5 * PI / 4,
		3 * PI / 2,
		7 * PI / 4
	};
	int					i;
	double				check_x;
	double				check_y;

	i = 0;
	while (i < 8)
	{
		check_x = x + cos(angles[i]) * (PLAYER_RADIUS + WALL_BUFFER);
		check_y = y + sin(angles[i]) * (PLAYER_RADIUS + WALL_BUFFER);
		if (is_wall(g, check_x, check_y))
			return (1);
		i++;
	}
	return (0);
}

void	move_with_collision(t_game *g, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = g->player.x + dx;
	new_y = g->player.y + dy;
	if (!check_collision_circle(g, new_x, new_y))
	{
		g->player.x = new_x;
		g->player.y = new_y;
	}
	else if (!check_collision_circle(g, new_x, g->player.y))
		g->player.x = new_x;
	else if (!check_collision_circle(g, g->player.x, new_y))
		g->player.y = new_y;
}

void	apply_rotation(t_game *g, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	old_dir_x = g->player.dir_x;
	old_plane_x = g->player.plane_x;
	g->player.dir_x = old_dir_x * cos_angle - g->player.dir_y * sin_angle;
	g->player.dir_y = old_dir_x * sin_angle + g->player.dir_y * cos_angle;
	g->player.plane_x = old_plane_x * cos_angle
		- g->player.plane_y * sin_angle;
	g->player.plane_y = old_plane_x * sin_angle
		+ g->player.plane_y * cos_angle;
}

void	strafe_left(t_game *g)
{
	double	dx;
	double	dy;

	dx = g->player.plane_x * MOVE_SPEED;
	dy = g->player.plane_y * MOVE_SPEED;
	move_with_collision(g, -dx, -dy);
}

void	strafe_right(t_game *g)
{
	double	dx;
	double	dy;

	dx = g->player.plane_x * MOVE_SPEED;
	dy = g->player.plane_y * MOVE_SPEED;
	move_with_collision(g, dx, dy);
}
