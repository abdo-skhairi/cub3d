/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:32:29 by sabderra          #+#    #+#             */
/*   Updated: 2026/01/01 20:31:37 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_game_resources(t_game *g)
{
    if (g->tex_no.img)
        mlx_destroy_image(g->mlx, g->tex_no.img);
    if (g->tex_so.img)
        mlx_destroy_image(g->mlx, g->tex_so.img);
    if (g->tex_we.img)
        mlx_destroy_image(g->mlx, g->tex_we.img);
    if (g->tex_ea.img)
        mlx_destroy_image(g->mlx, g->tex_ea.img);
    if (g->img.img)
        mlx_destroy_image(g->mlx, g->img.img);
    if (g->win)
        mlx_destroy_window(g->mlx, g->win);
    if (g->mlx)
    {
        mlx_destroy_display(g->mlx);
        free(g->mlx);
    }
}

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
	g->img.img = mlx_new_image(g->mlx, g->win_w, g->win_h);
	g->img.addr = mlx_get_data_addr(
			g->img.img,
			&g->img.bpp,
			&g->img.line_len,
			&g->img.endian
			);
	draw_scene(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	return (0);
}

void free_data(t_data *dt)
{
	int i;

	if (dt->no)
		free(dt->no);
	if (dt->so)
		free(dt->so);
	if (dt->we)
		free(dt->we);
	if (dt->ea)
		free(dt->ea);
	if (dt->map)
	{
		i = 0;
		while (i < dt->map_height)
		{
			if (dt->map[i])
				free(dt->map[i]);
			i++;
		}
		free(dt->map);
	}
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
	free_data(&dt);
	free_game_resources(&g);
	return (0);
}