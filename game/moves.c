/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:36:48 by abdo              #+#    #+#             */
/*   Updated: 2026/02/02 18:51:12 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_forward(t_game *g)
{
	double	dx;
	double	dy;

	dx = g->player.dir_x * MOVE_SPEED;
	dy = g->player.dir_y * MOVE_SPEED;
	move_with_collision(g, dx, dy);
}

void	move_backward(t_game *g)
{
	double	dx;
	double	dy;

	dx = g->player.dir_x * MOVE_SPEED;
	dy = g->player.dir_y * MOVE_SPEED;
	move_with_collision(g, -dx, -dy);
}

void	rotate_right(t_game *g)
{
	apply_rotation(g, ROT_SPEED);
}

void	rotate_left(t_game *g)
{
	apply_rotation(g, -ROT_SPEED);
}
