/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:25:25 by maeskhai          #+#    #+#             */
/*   Updated: 2025/12/16 12:24:46 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing/cub3d.h"

void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x >= 1024 || y >= 768)
        return;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

int get_texture_pixel(t_img *texture, int x, int y)
{
    char *dst;

    if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
        return (0);
    dst = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
    return (*(unsigned int *)dst);
}

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

void move_backward(t_game *g)
{
    double nx = g->player.x - g->player.dir_x * MOVE_SPEED;
    double ny = g->player.y - g->player.dir_y * MOVE_SPEED;

    if (!is_wall(g, nx, g->player.y))
        g->player.x = nx;
    if (!is_wall(g, g->player.x, ny))
        g->player.y = ny;
}

void strafe_left(t_game *g)
{
    double nx = g->player.x - g->player.plane_x * MOVE_SPEED;
    double ny = g->player.y - g->player.plane_y * MOVE_SPEED;

    if (!is_wall(g, nx, g->player.y))
        g->player.x = nx;
    if (!is_wall(g, g->player.x, ny))
        g->player.y = ny;
}

void strafe_right(t_game *g)
{
    double nx = g->player.x + g->player.plane_x * MOVE_SPEED;
    double ny = g->player.y + g->player.plane_y * MOVE_SPEED;

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

void draw_scene(t_game *g)
{
    int x = 0;

    while (x < g->win_w)
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
            if (map_y < 0 || map_x < 0 || map_y >= g->map_h
                || !g->map[map_y]
                || map_x >= (int)ft_strlen(g->map[map_y]))
                break;
            if (g->map[map_y][map_x] == '1')
                hit = 1;
        }
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (map_x - g->player.x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - g->player.y + (1 - step_y) / 2) / ray_dir_y;
        if (perp_wall_dist <= 0)
            perp_wall_dist = 1e-6;
        int line_height = (int)(g->win_h / perp_wall_dist);
        int draw_start = -line_height / 2 + g->win_h / 2;
        int draw_end = line_height / 2 + g->win_h / 2;
        if (draw_start < 0)
            draw_start = 0;
        if (draw_end >= g->win_h)
            draw_end = g->win_h - 1;
        double wall_x;
        if (side == 0)
            wall_x = g->player.y + perp_wall_dist * ray_dir_y;
        else
            wall_x = g->player.x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);
        t_img *texture;
        if (side == 0)
            texture = (ray_dir_x > 0) ? &g->tex_ea : &g->tex_we;
        else
            texture = (ray_dir_y > 0) ? &g->tex_so : &g->tex_no;
        int tex_x = (int)(wall_x * texture->width);
        if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
            tex_x = texture->width - tex_x - 1;
        double step = 1.0 * texture->height / line_height;
        double tex_pos = (draw_start - g->win_h / 2 + line_height / 2) * step;
        int y = 0;
        while (y < g->win_h)
        {
            if (y < draw_start)
                put_pixel(&g->img, x, y, g->ceiling_color);
            else if (y > draw_end)
                put_pixel(&g->img, x, y, g->floor_color);
            else
            {
                int tex_y = (int)tex_pos & (texture->height - 1);
                tex_pos += step;
                int color = get_texture_pixel(texture, tex_x, tex_y);
                if (side == 1)
                    color = ((color >> 1) & 0x7F7F7F);
                put_pixel(&g->img, x, y, color);
            }
            y++;
        }
        x++;
    }
}

int close_game(t_game *g)
{
    mlx_destroy_window(g->mlx, g->win);
    exit(0);
    return (0);
}

int key_press(int keycode, t_game *g)
{
    if (keycode == KEY_ESC)
        close_game(g);
    if (keycode == KEY_W)
        g->keys.w = 1;
    if (keycode == KEY_S)
        g->keys.s = 1;
    if (keycode == KEY_A)
        g->keys.a = 1;
    if (keycode == KEY_D)
        g->keys.d = 1;
    if (keycode == KEY_LEFT)
        rotate_left(g);
    if (keycode == KEY_RIGHT)
        rotate_right(g);
    return (0);
}

int key_release(int keycode, t_game *g)
{
    if (keycode == KEY_W)
        g->keys.w = 0;
    if (keycode == KEY_S)
        g->keys.s = 0;
    if (keycode == KEY_A)
        g->keys.a = 0;
    if (keycode == KEY_D)
        g->keys.d = 0;
    return (0);
}

int game_loop(t_game *g)
{
    if (g->keys.w)
        move_forward(g);
    if (g->keys.s)
        move_backward(g);
    if (g->keys.a)
        strafe_left(g);
    if (g->keys.d)
        strafe_right(g);
    mlx_destroy_image(g->mlx, g->img.img);
    g->img.img = mlx_new_image(g->mlx, g->win_w, g->win_h);
    g->img.addr = mlx_get_data_addr(
        g->img.img,
        &g->img.bpp,
        &g->img.line_len,
        &g->img.endian
    );
    draw_scene(g);
    mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
    return (0);
}

void load_texture(t_game *g, t_img *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(
        g->mlx, path, &texture->width, &texture->height);
    if (!texture->img)
        exit(1);
    texture->addr = mlx_get_data_addr(
        texture->img, &texture->bpp,
        &texture->line_len, &texture->endian);
}

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
    g->ceiling_color = (dt->c.r << 16) | (dt->c.g << 8) | dt->c.b;
    g->floor_color = (dt->f.r << 16) | (dt->f.g << 8) | dt->f.b;
    g->mlx = mlx_init();
    load_texture(g, &g->tex_no, dt->no);
    load_texture(g, &g->tex_so, dt->so);
    load_texture(g, &g->tex_we, dt->we);
    load_texture(g, &g->tex_ea, dt->ea);
    g->win = mlx_new_window(g->mlx, g->win_w, g->win_h, "cub3D");
    g->img.img = mlx_new_image(g->mlx, g->win_w, g->win_h);
    g->img.addr = mlx_get_data_addr(
        g->img.img,
        &g->img.bpp,
        &g->img.line_len,
        &g->img.endian
    );
}

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
    mlx_hook(g.win, 17, 0, close_game, &g);
    mlx_loop_hook(g.mlx, game_loop, &g);
    mlx_loop(g.mlx);
    return (0);
}
