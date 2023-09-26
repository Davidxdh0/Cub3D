/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 09:26:37 by bfranco       #+#    #+#                 */
/*   Updated: 2023/09/26 15:26:36 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_vert_line(t_gen *gen, t_ray ray, int x)
{
	while (ray.drawStart < ray.drawEnd)
	{
		mlx_put_pixel(gen->win, x, ray.drawStart, ray.color);
		++ray.drawStart;
	}
}

void cast_ray(t_gen *gen, t_player *player, int x)
{
	t_ray	ray;

	ray.cameraX = 2 * player->x / (double)WIDTH - 1;
	ray.rayDirX = player->dirX + player->planeX * ray.cameraX;
	ray.rayDirY = player->dirY + player->planeY * ray.cameraX;
	ray.mapX = (int)player->x;
	ray.mapY = (int)player->y;
	ray.deltaDistX = 1e30;
	ray.deltaDistY = 1e30;
	if (ray.rayDirY != 0)
		ray.deltaDistX = fabs(1 / ray.rayDirX);
	if (ray.deltaDistY != 0)
		ray.deltaDistY = fabs(1 / ray.rayDirY);
	ray.hit = 0;
	if (ray.rayDirX < 0)
	{
		ray.stepX = -1;
		ray.sideDistX = (player->x - ray.mapX) * ray.deltaDistX;
	}
	else
	{
		ray.stepX = 1;
		ray.sideDistX = (ray.mapX + 1.0 - player->x) * ray.deltaDistX;
	}
	if (ray.rayDirY < 0)
	{
		ray.stepY = -1;
		ray.sideDistY = (player->y - ray.mapY) * ray.deltaDistY;
	}
	else
	{
		ray.stepY = 1;
		ray.sideDistY = (ray.mapY + 1.0 - player->y) * ray.deltaDistY;
	}
	while (ray.hit == 0)
	{
		if (ray.sideDistX < ray.sideDistY)
		{
			ray.sideDistX += ray.deltaDistX;
			ray.mapX += ray.stepX;
			ray.side = 0;
		}
		else
		{
			ray.sideDistY += ray.deltaDistY;
			ray.mapY += ray.stepY;
			ray.side = 1;
		}
		if (gen->map[ray.mapY][ray.mapX] > 0)
			ray.hit = 1;
	}
	if (ray.side == 0)
		ray.perpWallDist = ray.sideDistX - ray.deltaDistX;
	else
		ray.perpWallDist = ray.sideDistY - ray.deltaDistY;
	ray.lineHeight = (int)(HEIGHT / ray.perpWallDist);
	ray.drawStart = -ray.lineHeight / 2 + HEIGHT / 2;
	if (ray.drawStart < 0)
		ray.drawStart = 0;
	ray.drawEnd = ray.lineHeight / 2 + HEIGHT / 2;
	if (ray.drawEnd >= HEIGHT)
		ray.drawEnd = HEIGHT - 1;
	if (ray.side == 1)
		ray.color = 0x00FF00FF;
	else
		ray.color = 0x0000FFFF;
	draw_vert_line(gen, ray, x);
}
