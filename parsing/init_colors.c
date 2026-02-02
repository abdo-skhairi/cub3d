/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:04:11 by maeskhai          #+#    #+#             */
/*   Updated: 2026/01/22 15:11:18 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_parse_color(char *color, t_color *rgb, char *err)
{
	char	**arr;

	if (!color)
		return ;
	arr = ft_split_rgb(color, ',');
	if (!arr)
		ft_print_error(err, NULL, NULL);
	if (!arr[0] || !arr[1] || !arr[2] || arr[3])
		ft_print_error("Error\nInvalid Color Info!\n", NULL, NULL);
	rgb->r = ft_atoi_rgb(arr[0]);
	rgb->g = ft_atoi_rgb(arr[1]);
	rgb->b = ft_atoi_rgb(arr[2]);
	ft_free_map(arr);
}

void	ft_extract_color(t_data *dt)
{
	ft_parse_color(dt->f_color, &dt->f, "Error\nF_color allocation failed!\n");
	ft_parse_color(dt->c_color, &dt->c, "Error\nC_color allocation failed!\n");
	if ((dt->c.r < 0 || dt->c.r > 255) || (dt->c.g < 0 || dt->c.g > 255)
		|| (dt->c.b < 0 || dt->c.b > 255) || (dt->f.r < 0 || dt->f.r > 255)
		|| (dt->f.g < 0 || dt->f.g > 255) || (dt->f.b < 0 || dt->f.b > 255))
		ft_print_error("Error\nInvalid Color Info <0-255>!\n", NULL, NULL);
}

void	ft_init_color(char *line_no_spaces, t_data *dt)
{
	if (ft_strncmp(line_no_spaces, "F", 1) == 0)
	{
		if (dt->nb_f == 0)
			dt->f_color = ft_strdup_2(line_no_spaces + 1);
		dt->nb_f++;
		return ;
	}
	if (ft_strncmp(line_no_spaces, "C", 1) == 0)
	{
		if (dt->nb_c == 0)
			dt->c_color = ft_strdup_2(line_no_spaces + 1);
		dt->nb_c++;
		return ;
	}
}
