/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:11:55 by maeskhai          #+#    #+#             */
/*   Updated: 2025/11/24 16:32:22 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_skip_spaces_tabs(char *line)
{
	int i;
	int	j;
	char *new;

	i = 0;
	j = 0;
	new = malloc(ft_strlen(line) + 1);
	if (!new)
		return (NULL);
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			new[j] = line[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

void	ft_check_line(char *line,t_data *dt)
{
	char *line_no_spaces;

	line_no_spaces = NULL;
	if (dt->map_line_start == 0)
		line_no_spaces = ft_skip_spaces_tabs(line);
	if ((!line_no_spaces || line_no_spaces[0] == '\n') && dt->map_line_start == 0)
		return ;
	if ((ft_strncmp(line_no_spaces, "NO", 2) == 0
		|| ft_strncmp(line_no_spaces, "SO", 2) == 0
		|| ft_strncmp(line_no_spaces, "WE", 2) == 0
		|| ft_strncmp(line_no_spaces, "EA", 2) == 0) && dt->map_line_start == 0)
	{
		ft_init_vars(line_no_spaces, dt);
		return ;
	}
	if ((ft_strncmp(line_no_spaces, "F", 1) == 0
		|| ft_strncmp(line_no_spaces, "C", 1) == 0) && dt->map_line_start == 0)
	{
		ft_init_color(line_no_spaces, dt);
		if (dt->nb_f == 1 && dt->nb_c == 1)
			ft_extract_color(dt);
		return ;
	}
	if (dt->nb_no != 1 || dt->nb_so != 1 || dt->nb_we != 1 || dt->nb_ea != 1 || dt->nb_f != 1 || dt->nb_c != 1)
		ft_print_error("Error\nInvalid Texture or Color Info!\n", NULL, line_no_spaces);
	ft_init_map(line, dt);
	free(line_no_spaces);
}
