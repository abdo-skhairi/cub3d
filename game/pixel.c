/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:32:17 by sabderra          #+#    #+#             */
/*   Updated: 2026/02/02 18:53:27 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr
		+ (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0
		|| x >= texture->width || y >= texture->height)
		return (0);
	dst = texture->addr
		+ (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}

void	load_texture(t_game *g, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(
			g->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		ft_print_error("Error\nInvalid texture path\n", NULL, NULL);
		exit(1);
	}
	texture->addr = mlx_get_data_addr(
			texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
}

t_img	*select_texture(t_game *g, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			return (&g->tex_ea);
		return (&g->tex_we);
	}
	if (r->ray_dir_y > 0)
		return (&g->tex_so);
	return (&g->tex_no);
}

void	draw_column_pixel(t_game *g, t_ray *r,
	t_texcol *c, int x)
{
	int	y;
	int	tex_y;
	int	color;

	y = -1;
	while (++y < g->win_h)
	{
		if (y < c->draw_start)
			put_pixel(&g->img, x, y, g->ceiling_color);
		else if (y > c->draw_end)
			put_pixel(&g->img, x, y, g->floor_color);
		else
		{
			tex_y = (int)c->tex_pos;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= c->tex->height)
				tex_y = c->tex->height - 1;
			color = get_texture_pixel(c->tex, c->tex_x, tex_y);
			if (r->side == 1)
				color = ((color >> 1) & 0x7F7F7F);
			put_pixel(&g->img, x, y, color);
			c->tex_pos += c->step;
		}
	}
}
