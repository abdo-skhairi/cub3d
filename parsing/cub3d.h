/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:29:24 by maeskhai          #+#    #+#             */
/*   Updated: 2025/12/16 12:25:37 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif


#define TILE_SIZE 32
#define PLAYER_SIZE 8
#define MOVE_SPEED  0.06
#define ROT_SPEED   0.06

/* macOS key codes */
#ifdef __APPLE__
# define KEY_ESC    53
# define KEY_W      13
# define KEY_A      0
# define KEY_S      1
# define KEY_D      2
# define KEY_LEFT   123
# define KEY_RIGHT  124
#else
/* Linux key codes */
// # define KEY_ESC    65307
// # define KEY_W      119
// # define KEY_A      97
// # define KEY_S      115
// # define KEY_D      100
// # define KEY_LEFT   65361
// # define KEY_RIGHT  65363
#endif

#include "mlx.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
#include <math.h>

# include "./get_next_line/get_next_line.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_keys
{
    int w;
    int s;
    int a;
    int d;
}   t_keys;


typedef struct	s_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f_color;
	char	*c_color;
	int	nb_no;
	int nb_so;
	int nb_we;
	int nb_ea;
	int nb_f;
	int nb_c;
	int fd;
	t_color	f;
	t_color	c;
	int map_line_start;
	char	**map;
	int	map_height;
	int	player_x;
	int	player_y;
	char	player_dir;
	int		map_last_line;
}	t_data;


typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
}   t_img;

typedef struct s_game
{
    void        *mlx;
    void        *win;

    int         win_w;
    int         win_h;

    char        **map;
    int         map_w;
    int         map_h;

    t_player    player;
    t_img       img;
    t_keys      keys;
	int         floor_color;
	int         ceiling_color;
	t_img       tex_no;
	t_img       tex_so;
	t_img       tex_we;
	t_img       tex_ea;
}   t_game;

//------------//parsing :

void    ft_parsing(char *str, t_data *dt);
void	ft_check_file_name(char *s);
void	ft_print_error(char *s, char **map, char *line);
void	ft_free_map(char **map);
void	ft_read_fd(char *fd_in, t_data *dt);
void	ft_check_line(char *line, t_data *dt);
char	*ft_get_texture(char *s);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_get_color(char *s);
void	ft_init_color(char *line, t_data *dt);
char	*ft_get_texture(char *s);
char	*ft_get_color(char *s);
void    ft_init_map(char *line, t_data *dt);
void    ft_extract_color(t_data *dt);
void	ft_check_map_error(t_data *dt);
void	ft_init_vars(char *line_no_spaces, t_data *dt);
void	ft_init_color(char *line_no_spaces, t_data *dt);
void	ft_extract_color(t_data *dt);
void	ft_check_map_error(t_data *dt);

//------------//utils :
char	*ft_strtrim(char *s1, char *set);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup_2(char *s1);
char	**ft_split_rgb(char *s, char c);
char	**ft_split(char *s, char c);
int		ft_atoi_rgb(char *nptr);

#endif