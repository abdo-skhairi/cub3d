/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_rgb2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:18:41 by maeskhai          #+#    #+#             */
/*   Updated: 2026/01/22 14:11:24 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	check_color_separators(char *s, char c)
{
	int	i;
	int	nb_c;

	i = 0;
	nb_c = 0;
	while (s[i])
	{
		if (s[i] == c)
			nb_c++;
		i++;
	}
	if (nb_c == 3)
		ft_print_error("Error\nInvalid Color Info!\n", NULL, NULL);
}

static int	count_words(char *s, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			w++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (w);
}

int	ft_nwords(char *s, char c)
{
	check_color_separators(s, c);
	return (count_words(s, c));
}
