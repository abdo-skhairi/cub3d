/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:05:41 by abdo              #+#    #+#             */
/*   Updated: 2026/02/02 19:05:52 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_colors(t_game *g, t_data *dt)
{
	g->ceiling_color = (dt->c.r << 16)
		| (dt->c.g << 8) | dt->c.b;
	g->floor_color = (dt->f.r << 16)
		| (dt->f.g << 8) | dt->f.b;
}

void	init_textures(t_game *g, t_data *dt)
{
	g->mlx = mlx_init();
	load_texture(g, &g->tex_no, dt->no);
	load_texture(g, &g->tex_so, dt->so);
	load_texture(g, &g->tex_we, dt->we);
	load_texture(g, &g->tex_ea, dt->ea);
}
