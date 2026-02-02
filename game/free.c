/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:46:17 by abdo              #+#    #+#             */
/*   Updated: 2026/02/02 18:52:25 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_image(void *mlx, void **img)
{
	if (*img)
	{
		mlx_destroy_image(mlx, *img);
		*img = NULL;
	}
}

void	free_game_resources(t_game *g)
{
	if (!g)
		return ;
	destroy_image(g->mlx, &g->img.img);
	destroy_image(g->mlx, &g->tex_no.img);
	destroy_image(g->mlx, &g->tex_so.img);
	destroy_image(g->mlx, &g->tex_we.img);
	destroy_image(g->mlx, &g->tex_ea.img);
	if (g->win)
	{
		mlx_destroy_window(g->mlx, g->win);
		g->win = NULL;
	}
	if (g->mlx)
	{
		free(g->mlx);
		g->mlx = NULL;
	}
	if (g->map)
	{
		ft_free_map(g->map);
		g->map = NULL;
	}
}

int	close_game(t_game *g)
{
	free_game_resources(g);
	exit(0);
	return (0);
}
