/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 09:26:37 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/08 14:53:08 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "cub3d.h"

static void	draw_vert_line_textures(t_gen *gen, t_ray *ray, int x)
{
	if (ray->side == 0)
	{
		ray->walldist = ray->sidedist_x - ray->deltadist_x;
		ray->wall_x = gen->player.y + ray->walldist * ray->raydir_y;
	}
	else
	{
		ray->walldist = ray->sidedist_y - ray->deltadist_y;
		ray->wall_x = gen->player.x + ray->walldist * ray->raydir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
	ray->height = (int)(HEIGHT / ray->walldist);
	ray->start = -ray->height / 2 + HEIGHT / 2;
	ray->end = ray->height / 2 + HEIGHT / 2;
	if (ray->start < 0)
		ray->start = 0;
	if (ray->end >= HEIGHT)
		ray->end = HEIGHT - 1;
	draw_pixels(gen, ray, x);
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
	ray.side = 0;
	calc_side_dist(player, &ray);
	calc_wall_dist(gen, &ray);
	draw_vert_line_textures(gen, &ray, x);
	draw_vision(gen, player, ray);
}
