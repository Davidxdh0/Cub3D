/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 09:26:37 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/04 16:06:54 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(int color)
{
	if (color == 1)
		return (0x000000FF);
	else if (color == 2)
		return (0x0000FFFF);
	else if (color == 3)
		return (0x00FF00FF);
	else
		return (0xFF0000FF);
}

int	get_color_textures(uint8_t *pixel)
{
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

void	draw_vert_line_textures(t_gen *gen, t_ray *ray, int x)
{
		//texturing calculations
	int texNum = 0;
	texNum++;
	if (ray->side == 0)
		ray->walldist = ray->sidedist_x - ray->deltadist_x;
	else
		ray->walldist = ray->sidedist_y - ray->deltadist_y;
	int texY = 0;
	if (TESTMAP)
		texNum = gen->map[(int)ray->map_y][(int)ray->map_x] - 1;

	double wallX;
	if (ray->side == 0)
		wallX = ray->map_y + ray->walldist * ray->raydir_y;
	else
		wallX = ray->map_x + ray->walldist * ray->raydir_x;
	wallX -= floor((wallX));
	ray->height = (int)(HEIGHT / ray->walldist);
	ray->start = -ray->height / 2 + HEIGHT / 2;
	ray->end = ray->height / 2 + HEIGHT / 2;
	if (ray->start < 0)
		ray->start = 0;
	if (ray->end >= HEIGHT)
		ray->end = HEIGHT - 1;
	int texX = (int)(wallX * (double)(gen->txtrs.t_no->width));
	if(ray->side == 0 && ray->raydir_x > 0) texX = gen->txtrs.t_no->width - texX - 1;
	if(ray->side == 1 && ray->raydir_y < 0) texX = gen->txtrs.t_no->width - texX - 1;
	double step = 1.0 * gen->txtrs.t_no->height / ray->height;
	double texPos = (ray->start - (int)HEIGHT  / 2 + ray->height / 2) * step;
	// printf("start[%d:%d] end: %d height: %d\n", ray->start, x, ray->end, ray->height);
	while (ray->start < ray->end)
 	{
		texY = (int)texPos & (gen->txtrs.t_no->height - 1);
		texPos += step;
		ray->color = get_color_textures(gen->txtrs.t_no->pixels + (gen->txtrs.t_no->height * texY + texX) \
				* gen->txtrs.t_no->bytes_per_pixel);
		mlx_put_pixel(gen->win, WIDTH - x, ray->start, ray->color);
		// printf("start[%d:%d] %d\n", ray->start, x, ray->end);
		++ray->start;
	}
}

void	draw_vert_line(t_gen *gen, t_ray *ray, int x)
{
	if (ray->side == 0)
		ray->walldist = ray->sidedist_x - ray->deltadist_x;
	else
		ray->walldist = ray->sidedist_y - ray->deltadist_y;
	ray->height = (int)(HEIGHT / ray->walldist);
	ray->start = -ray->height / 2 + HEIGHT / 2;
	ray->end = ray->height / 2 + HEIGHT / 2;
	if (ray->start < 0)
		ray->start = 0;
	if (ray->end >= HEIGHT)
		ray->end = HEIGHT - 1;
	if (ray->side == 1)
		ray->color = get_color(gen->map[(int)ray->map_y][(int)ray->map_x]);
	else
		ray->color = get_color(gen->map[(int)ray->map_y][(int)ray->map_x]) / 2;
	while (ray->start < ray->end)
	{
		mlx_put_pixel(gen->win, WIDTH - x, ray->start, ray->color);
		++ray->start;
	}
}


void	calc_side_dist(t_player *player, t_ray *ray)
{
	if (ray->raydir_x != 0)
		ray->deltadist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y != 0)
		ray->deltadist_y = fabs(1 / ray->raydir_y);
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->y) * ray->deltadist_y;
	}
}

void	calc_wall_dist(t_gen *gen, t_ray *ray)
{
	while (gen->map[(int)ray->map_y][(int)ray->map_x] == '0')
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			if (ray->map_x > gen->width - 1)
				ray->map_x = gen->width - 1;
			if (ray->map_x < 0)
				ray->map_x = 0;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			if (ray->map_y > gen->height - 1)
				ray->map_y = gen->height - 1;
			if (ray->map_y < 0)
				ray->map_y = 0;
			ray->side = 1;
		}
	}
}

void	draw_vision(t_gen *gen, t_player *player, t_ray ray)
{
	t_vector	line;

	line.x = ray.map_x;
	line.y = ray.map_y;
	if (ray.side == 0)
		line.x = player->x + ray.walldist * ray.raydir_x;
	else
		line.y = player->y + ray.walldist * ray.raydir_y;
	// printf("x: %d, y: %d\n", (int)((ray.sidedist_x - (int)ray.sidedist_x) * 64), (int)((ray.sidedist_y - (int)ray.sidedist_y) * 64));
	// printf("player->dir_x: %f, player->dir_y: %f\n", player->dir_x, player->dir_y);
	bresenham(gen, player->x * gen->sq_size, player->y * gen->sq_size, \
	line.x * gen->sq_size, line.y * gen->sq_size);
}

void	cast_ray(t_gen *gen, t_player *player, int x)
{
	t_ray		ray;

	ray.camera_x = 2 * x / (double)WIDTH - 1;
	ray.raydir_x = player->dir_x + player->plane_x * ray.camera_x;
	ray.raydir_y = player->dir_y + player->plane_y * ray.camera_x;
	ray.map_x = (int)player->x;
	ray.map_y = (int)player->y;
	
	ray.deltadist_x = 1e30;
	ray.deltadist_y = 1e30;
	calc_side_dist(player, &ray);
	calc_wall_dist(gen, &ray);
	// printf("sidedist x = %f y %f, raymapx %f mapy %f\n", ray.sidedist_x, ray.sidedist_y, ray.map_x, ray.map_y);
	if (TESTMAP == 0)
		draw_vert_line(gen, &ray, x);
	if (TESTMAP == 1)
		draw_vert_line_textures(gen, &ray, x);
	draw_vision(gen, player, ray);
	
}
