/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:18:14 by maeskhai          #+#    #+#             */
/*   Updated: 2025/12/25 15:25:15 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_file_name(char *str)
{
	int len;
	
	len = ft_strlen(str);
	len--;
	if (str[len] == 'b' && str[len - 1] == 'u' && str[len - 2] == 'c' && str[len - 3] == '.')
		return ;
	ft_print_error("Error\nInvalid file name!\n", NULL, NULL);
}
