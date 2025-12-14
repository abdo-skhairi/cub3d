/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:25:25 by maeskhai          #+#    #+#             */
/*   Updated: 2025/12/14 19:15:41 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing/cub3d.h"
#include <math.h>
#include <stdlib.h>

#define TILE_SIZE   32
#define PLAYER_SIZE 8
#define MOVE_SPEED  0.06
#define ROT_SPEED   0.06

/* ========================== PIXEL ========================== */

void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x >= 1024 || y >= 768)
        return ;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}



/* ========================== DRAW ========================== */

void draw_square(t_img *img, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            put_pixel(img, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void draw_line(t_game *g, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        put_pixel(&g->img, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_fov_rays(t_game *g)
{
    int num_rays = 60;
    int i;
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    double ray_x;
    double ray_y;
    double step_x;
    double step_y;
    int steps;
    int j;
    int px = (int)(g->player.x * TILE_SIZE);
    int py = (int)(g->player.y * TILE_SIZE);
    int hit;

    i = 0;
    while (i < num_rays)
    {
        camera_x = 2 * i / (double)num_rays - 1;
        ray_dir_x = g->player.dir_x + g->player.plane_x * camera_x;
        ray_dir_y = g->player.dir_y + g->player.plane_y * camera_x;

        ray_x = g->player.x;
        ray_y = g->player.y;
        
        steps = 100;
        step_x = ray_dir_x * 0.1;
        step_y = ray_dir_y * 0.1;
        
        j = 0;
        hit = 0;
        while (j < steps && !hit)
        {
            ray_x += step_x;
            ray_y += step_y;
            
            if (ray_x < 0 || ray_y < 0 || (int)ray_y >= g->map_h)
            {
                hit = 1;
                break;
            }
            if (g->map[(int)ray_y] && (int)ray_x < (int)ft_strlen(g->map[(int)ray_y]))
            {
                if (g->map[(int)ray_y][(int)ray_x] == '1')
                    hit = 1;
            }
            else
                hit = 1;
            j++;
        }
        
        draw_line(g, px, py, (int)(ray_x * TILE_SIZE), (int)(ray_y * TILE_SIZE), 0x00FF00);
        i++;
    }
}

void draw_player(t_game *g)
{
    int px = (int)(g->player.x * TILE_SIZE);
    int py = (int)(g->player.y * TILE_SIZE);
    int i;
    int j;

    i = -PLAYER_SIZE / 2;
    while (i <= PLAYER_SIZE / 2)
    {
        j = -PLAYER_SIZE / 2;
        while (j <= PLAYER_SIZE / 2)
        {
            if (i * i + j * j <= (PLAYER_SIZE / 2) * (PLAYER_SIZE / 2))
                put_pixel(&g->img, px + j, py + i, 0xFF8800);
            j++;
        }
        i++;
    }
}

void draw_minimap(t_game *g)
{
    int y;
    int x;
    int walls = 0;
    int floors = 0;
    int voids = 0;

    y = 0;
    while (y < g->map_h)
    {
        x = 0;
        if (g->map[y])
        {
            while (g->map[y][x])
            {
                if (g->map[y][x] == '1')
                    draw_square(&g->img, x * TILE_SIZE, y * TILE_SIZE, 0x0000FF);
                else if (g->map[y][x] == '0' || g->map[y][x] == 'N' || 
                         g->map[y][x] == 'S' || g->map[y][x] == 'E' || g->map[y][x] == 'W')
                    draw_square(&g->img, x * TILE_SIZE, y * TILE_SIZE, 0xFFFFFF);
                else
                    draw_square(&g->img, x * TILE_SIZE, y * TILE_SIZE, 0x000000);
                if (g->map[y][x] == '1')
                    walls++;
                else if (g->map[y][x] == '0' || g->map[y][x] == 'N' || g->map[y][x] == 'S' || g->map[y][x] == 'E' || g->map[y][x] == 'W')
                    floors++;
                else
                    voids++;
                x++;
            }
        }
        y++;
    }
    
    draw_fov_rays(g);
    draw_player(g);
    fprintf(stderr, "[minimap] map_h=%d walls=%d floors=%d voids=%d player_px=%d player_py=%d\n",
            g->map_h, walls, floors, voids, (int)(g->player.x * TILE_SIZE), (int)(g->player.y * TILE_SIZE));
}

/* ========================== MOVEMENT ========================== */

int is_wall(t_game *g, double x, double y)
{
    if (x < 0 || y < 0)
        return (1);
    if ((int)y >= g->map_h)
        return (1);
    if (!g->map[(int)y])
        return (1);
    if ((int)x >= (int)ft_strlen(g->map[(int)y]))
        return (1);
    if (g->map[(int)y][(int)x] == '1')
        return (1);
    return (0);
}

void move_forward(t_game *g)
{
    double nx = g->player.x + g->player.dir_x * MOVE_SPEED;
    double ny = g->player.y + g->player.dir_y * MOVE_SPEED;

    if (!is_wall(g, nx, g->player.y))
        g->player.x = nx;
    if (!is_wall(g, g->player.x, ny))
        g->player.y = ny;
}

void draw_scene(t_game *g)
{
    int x;
                for (x = 0; x < g->win_w; x++)
                {
                    double camera_x = 2 * x / (double)g->win_w - 1;
                    double ray_dir_x = g->player.dir_x + g->player.plane_x * camera_x;
                    double ray_dir_y = g->player.dir_y + g->player.plane_y * camera_x;

                    int map_x = (int)g->player.x;
                    int map_y = (int)g->player.y;

                    double side_dist_x;
                    double side_dist_y;

                    double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
                    double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
                    int step_x;
                    int step_y;

                    int hit = 0;
                    int side = 0;

                    if (ray_dir_x < 0)
                    {
                        step_x = -1;
                        side_dist_x = (g->player.x - map_x) * delta_dist_x;
                    }
                    else
                    {
                        step_x = 1;
                        side_dist_x = (map_x + 1.0 - g->player.x) * delta_dist_x;
                    }
                    if (ray_dir_y < 0)
                    {
                        step_y = -1;
                        side_dist_y = (g->player.y - map_y) * delta_dist_y;
                    }
                    else
                    {
                        step_y = 1;
                        side_dist_y = (map_y + 1.0 - g->player.y) * delta_dist_y;
                    }

                    while (!hit)
                    {
                        if (side_dist_x < side_dist_y)
                        {
                            side_dist_x += delta_dist_x;
                            map_x += step_x;
                            side = 0;
                        }
                        else
                        {
                            side_dist_y += delta_dist_y;
                            map_y += step_y;
                            side = 1;
                        }
                        if (map_y < 0 || map_x < 0 || map_y >= g->map_h || !g->map[map_y] || map_x >= (int)ft_strlen(g->map[map_y]))
                        {
                            hit = 1;
                            break;
                        }
                        if (g->map[map_y][map_x] == '1')
                            hit = 1;
                    }

                    double perp_wall_dist;
                    if (side == 0)
                    {
                        if (ray_dir_x == 0)
                            perp_wall_dist = 1e30;
                        else
                            perp_wall_dist = (map_x - g->player.x + (1 - step_x) / 2) / ray_dir_x;
                    }
                    else
                    {
                        if (ray_dir_y == 0)
                            perp_wall_dist = 1e30;
                        else
                            perp_wall_dist = (map_y - g->player.y + (1 - step_y) / 2) / ray_dir_y;
                    }
                    if (perp_wall_dist <= 0) perp_wall_dist = 1e-6;

                    int line_height = (int)(g->win_h / perp_wall_dist);
                    int draw_start = -line_height / 2 + g->win_h / 2;
                    int draw_end = line_height / 2 + g->win_h / 2;
                    if (draw_start < 0) draw_start = 0;
                    if (draw_end >= g->win_h) draw_end = g->win_h - 1;

                    int color = 0xAAAAAA;
                    if (side == 1) color = (color >> 1) & 0x7F7F7F;

                    int y;
                    for (y = 0; y < g->win_h; y++)
                    {
                        if (y < draw_start)
                            put_pixel(&g->img, x, y, g->ceiling_color);
                        else if (y > draw_end)
                            put_pixel(&g->img, x, y, g->floor_color);
                        else
                            put_pixel(&g->img, x, y, color);
                    }
                }
}

void move_backward(t_game *g)
{
    double nx = g->player.x - g->player.dir_x * MOVE_SPEED;
    double ny = g->player.y - g->player.dir_y * MOVE_SPEED;

    if (!is_wall(g, nx, g->player.y))
        g->player.x = nx;
    if (!is_wall(g, g->player.x, ny))
        g->player.y = ny;
}

void rotate_left(t_game *g)
{
    double old_dir_x = g->player.dir_x;
    double old_plane_x = g->player.plane_x;

    g->player.dir_x = g->player.dir_x * cos(ROT_SPEED)
                    - g->player.dir_y * sin(ROT_SPEED);
    g->player.dir_y = old_dir_x * sin(ROT_SPEED)
                    + g->player.dir_y * cos(ROT_SPEED);
    
    g->player.plane_x = g->player.plane_x * cos(ROT_SPEED)
                      - g->player.plane_y * sin(ROT_SPEED);
    g->player.plane_y = old_plane_x * sin(ROT_SPEED)
                      + g->player.plane_y * cos(ROT_SPEED);
}

void rotate_right(t_game *g)
{
    double old_dir_x = g->player.dir_x;
    double old_plane_x = g->player.plane_x;

    g->player.dir_x = g->player.dir_x * cos(-ROT_SPEED)
                    - g->player.dir_y * sin(-ROT_SPEED);
    g->player.dir_y = old_dir_x * sin(-ROT_SPEED)
                    + g->player.dir_y * cos(-ROT_SPEED);
    
    g->player.plane_x = g->player.plane_x * cos(-ROT_SPEED)
                      - g->player.plane_y * sin(-ROT_SPEED);
    g->player.plane_y = old_plane_x * sin(-ROT_SPEED)
                      + g->player.plane_y * cos(-ROT_SPEED);
}

/* ========================== INPUT ========================== */

int key_press(int keycode, t_game *g)
{
    if (keycode == 65307)
        exit(0);
    if (keycode == 'w')
        g->keys.w = 1;
    if (keycode == 's')
        g->keys.s = 1;
    if (keycode == 'a')
        g->keys.a = 1;
    if (keycode == 'd')
        g->keys.d = 1;
    return (0);
}

int key_release(int keycode, t_game *g)
{
    if (keycode == 'w')
        g->keys.w = 0;
    if (keycode == 's')
        g->keys.s = 0;
    if (keycode == 'a')
        g->keys.a = 0;
    if (keycode == 'd')
        g->keys.d = 0;
    return (0);
}

/* ========================== LOOP ========================== */

int game_loop(t_game *g)
{
    if (g->keys.w)
        move_forward(g);
    if (g->keys.s)
        move_backward(g);
    if (g->keys.a)
        rotate_left(g);
    if (g->keys.d)
        rotate_right(g);

    mlx_destroy_image(g->mlx, g->img.img);
    g->img.img = mlx_new_image(g->mlx, g->win_w, g->win_h);
    g->img.addr = mlx_get_data_addr(
        g->img.img,
        &g->img.bpp,
        &g->img.line_len,
        &g->img.endian
    );

    draw_scene(g);
    // draw_minimap(g);
    mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
    return (0);
}

/* ========================== INIT ========================== */

void init_game(t_game *g, t_data *dt)
{
    g->win_w = 1024;
    g->win_h = 768;
    g->map = dt->map;
    g->map_h = dt->map_height;

    g->keys.w = 0;
    g->keys.s = 0;
    g->keys.a = 0;
    g->keys.d = 0;

    g->player.x = dt->player_x + 0.5;
    g->player.y = dt->player_y + 0.5;

    g->player.dir_x = 0;
    g->player.dir_y = 0;
    if (dt->player_dir == 'N')
        g->player.dir_y = -1;
    if (dt->player_dir == 'S')
        g->player.dir_y = 1;
    if (dt->player_dir == 'E')
        g->player.dir_x = 1;
    if (dt->player_dir == 'W')
        g->player.dir_x = -1;

    g->player.plane_x = 0;
    g->player.plane_y = 0;
    if (dt->player_dir == 'N')
        g->player.plane_x = 0.66;
    if (dt->player_dir == 'S')
        g->player.plane_x = -0.66;
    if (dt->player_dir == 'E')
        g->player.plane_y = 0.66;
    if (dt->player_dir == 'W')
        g->player.plane_y = -0.66;
    /* set ceiling and floor colors from parsed data (default if missing) */
    if (dt->c.r >= 0 && dt->c.g >= 0 && dt->c.b >= 0)
        g->ceiling_color = (dt->c.r << 16) | (dt->c.g << 8) | dt->c.b;
    else
        g->ceiling_color = 0x87CEEB; /* sky blue */

    if (dt->f.r >= 0 && dt->f.g >= 0 && dt->f.b >= 0)
        g->floor_color = (dt->f.r << 16) | (dt->f.g << 8) | dt->f.b;
    else
        g->floor_color = 0x404040; /* dark gray */

    fprintf(stderr, "[debug] map_h=%d player=(%.1f,%.1f) dir=%c\n", g->map_h, g->player.x, g->player.y, dt->player_dir);

    g->mlx = mlx_init();
    g->win = mlx_new_window(g->mlx, g->win_w, g->win_h, "cub3D");
    g->img.img = mlx_new_image(g->mlx, g->win_w, g->win_h);
    g->img.addr = mlx_get_data_addr(
        g->img.img,
        &g->img.bpp,
        &g->img.line_len,
        &g->img.endian
    );
}

/* ========================== MAIN ========================== */

int main(int ac, char **av)
{
    t_data dt;
    t_game g;

    if (ac != 2)
        ft_print_error("Error\nInvalid arguments\n", NULL, NULL);

    ft_parsing(av[1], &dt);
    init_game(&g, &dt);

    mlx_hook(g.win, 2, 1L << 0, key_press, &g);
    mlx_hook(g.win, 3, 1L << 1, key_release, &g);
    mlx_loop_hook(g.mlx, game_loop, &g);
    mlx_loop(g.mlx);
    return (0);
}
