/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Textures_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:27:11 by maeskhai          #+#    #+#             */
/*   Updated: 2025/11/24 16:28:08 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_vars(char *line_no_spaces, t_data *dt)
{
	if (ft_strncmp(line_no_spaces, "NO", 2) == 0)
	{
		if (dt->nb_no == 0)
			dt->no = ft_strdup_2(line_no_spaces + 2);
		dt->nb_no++;
		return ;
	}
	else if (ft_strncmp(line_no_spaces, "SO", 2) == 0)
	{
		if (dt->nb_so == 0)
			dt->so = ft_strdup_2(line_no_spaces + 2);
		dt->nb_so++;
		return ;
	}
	else if (ft_strncmp(line_no_spaces, "WE", 2) == 0)
	{
		if (dt->nb_we == 0)
			dt->we = ft_strdup_2(line_no_spaces + 2);
		dt->nb_we++;
		return ;
	}
	else if (ft_strncmp(line_no_spaces, "EA", 2) == 0)
	{
		if (dt->nb_ea == 0)
			dt->ea = ft_strdup_2(line_no_spaces + 2);
		dt->nb_ea++;
		return ;
	}
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

void	ft_extract_color(t_data *dt)
{
	char	**arr;

	if (dt->f_color)
	{
		arr = ft_split_rgb(dt->f_color, ',');
		if (!arr)
			ft_print_error("Error\nF_color allocation failed!\n", NULL, NULL);
		if (!arr[0] || !arr[1] || !arr[2] || arr[3])
			ft_print_error("Error\nInvalid F_color Info!\n", NULL, NULL);
		dt->f.r = ft_atoi_rgb(arr[0]);
		dt->f.g = ft_atoi_rgb(arr[1]);
		dt->f.b = ft_atoi_rgb(arr[2]);
		ft_free_map(arr);
	}
	if (dt->c_color)
	{
		arr = ft_split_rgb(dt->c_color, ',');
		if (!arr)
			ft_print_error("Error\nC_color allocation failed!\n", NULL, NULL);
		if (!arr[0] || !arr[1] || !arr[2] || arr[3])
			ft_print_error("Error\nInvalid C_color Info!\n", NULL, NULL);
		dt->c.r = ft_atoi_rgb(arr[0]);
		dt->c.g = ft_atoi_rgb(arr[1]);
		dt->c.b = ft_atoi_rgb(arr[2]);
		ft_free_map(arr);
	}
	if ((dt->c.r < 0 || dt->c.r > 255) || (dt->c.g < 0 || dt->c.g > 255)
		|| (dt->c.b < 0 || dt->c.b > 255) || (dt->f.r < 0 || dt->f.r > 255)
		|| (dt->f.g < 0 || dt->f.g > 255) || (dt->f.b < 0 || dt->f.b > 255))
		ft_print_error("Error\nInvalid Color Info <0-255>!\n", NULL, NULL);
}
