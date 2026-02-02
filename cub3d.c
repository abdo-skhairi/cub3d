/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:32:29 by sabderra          #+#    #+#             */
/*   Updated: 2026/01/29 18:41:58 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game	*g)
{
	if (g->keys.w)
		move_forward(g);
	if (g->keys.s)
		move_backward(g);
	if (g->keys.a)
		strafe_left(g);
	if (g->keys.d)
		strafe_right(g);
	mlx_destroy_image(g->mlx, g->img.img);
	g->img.img = NULL;
	g->img.img = mlx_new_image(g->mlx, g->win_w, g->win_h);
	g->img.width = g->win_w;
	g->img.height = g->win_h;
	draw_scene(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	return (0);
}

int	main(int ac, char	**av)
{
	t_data	dt;
	t_game	g;

	if (ac != 2)
		ft_print_error("Error\nInvalid arguments\n", NULL, NULL);
	ft_parsing(av[1], &dt);
	init_game(&g, &dt);
	mlx_hook(g.win, EVENT_KEY_PRESS, KEY_PRESS_MASK, key_press, &g);
	mlx_hook(g.win, EVENT_KEY_RELEASE, KEY_RELEASE_MASK, key_release, &g);
	mlx_hook(g.win, EVENT_CLOSE, 0, close_game, &g);
	mlx_loop_hook(g.mlx, game_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}
