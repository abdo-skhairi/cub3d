/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:27:11 by maeskhai          #+#    #+#             */
/*   Updated: 2026/01/22 15:11:41 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_path(char *s)
{
	if (s[0] != 't')
		ft_print_error("Error\nInvalid Textures Info!\n", NULL, NULL);
	return ;
}

static int	ft_init_no_so(char *line_no_spaces, t_data *dt)
{
	if (ft_strncmp(line_no_spaces, "NO", 2) == 0)
	{
		if (dt->nb_no == 0)
		{
			dt->no = ft_strdup_2(line_no_spaces + 2);
			ft_check_path(dt->no);
		}
		dt->nb_no++;
		return (1);
	}
	else if (ft_strncmp(line_no_spaces, "SO", 2) == 0)
	{
		if (dt->nb_so == 0)
		{
			dt->so = ft_strdup_2(line_no_spaces + 2);
			ft_check_path(dt->so);
		}
		dt->nb_so++;
		return (1);
	}
	return (0);
}

static void	ft_init_we_ea(char *line_no_spaces, t_data *dt)
{
	if (ft_strncmp(line_no_spaces, "WE", 2) == 0)
	{
		if (dt->nb_we == 0)
		{
			dt->we = ft_strdup_2(line_no_spaces + 2);
			ft_check_path(dt->we);
		}
		dt->nb_we++;
	}
	else if (ft_strncmp(line_no_spaces, "EA", 2) == 0)
	{
		if (dt->nb_ea == 0)
		{
			dt->ea = ft_strdup_2(line_no_spaces + 2);
			ft_check_path(dt->ea);
		}
		dt->nb_ea++;
	}
}

void	ft_init_vars(char *line_no_spaces, t_data *dt)
{
	if (ft_init_no_so(line_no_spaces, dt))
		return ;
	ft_init_we_ea(line_no_spaces, dt);
}
