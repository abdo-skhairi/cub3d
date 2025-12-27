/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:14:06 by maeskhai          #+#    #+#             */
/*   Updated: 2025/12/25 15:22:13 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_atoi_rgb(char *str)
{
	int			i;
	int			sign;
	long long	tot;

	i = 0;
	sign = 1;
	tot = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		ft_print_error("Error\nInvalid Color Info(rgb wrong)!\n", NULL, NULL);
	while (str[i] >= '0' && str[i] <= '9')
	{
		tot = (tot * 10) + (str[i] - 48);
		if (tot > 9223372036854775807 && sign == 1)
			return (-1);
		if (tot > 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
		ft_print_error("Error\nInvalid Color Info(rgb wrong)!\n", NULL, NULL);
	return (tot * sign);
}
