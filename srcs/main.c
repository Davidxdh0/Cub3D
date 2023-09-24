#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <math.h>
#include "cub3d.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SIZE 16
#define WIDTH 800
#define HEIGHT 600

int worldMap[MAP_WIDTH][MAP_HEIGHT] = \
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


void	init_gen(t_gen *gen, mlx_t *mlx)
{
	gen->mlx = mlx;
	gen->win = mlx_new_image(mlx, WIDTH, HEIGHT);
	gen->player.x = 22;
	gen->player.y = 12;
	gen->player.dirX = -1;
	gen->player.dirY = 0;
	gen->player.planeX = 0;
	gen->player.planeY = 0.66;
	gen->player.img = mlx_new_image(mlx, 3, 3);
	memset(gen->player.img->data, 0xFF000000, 9);
}

// void	calc_delta(t_vector *deltaDist, t_vector *ray)
// {
// 	if (ray->y == 0)
// 		deltaDist->x = 1e30;
// 	else
// 		deltaDist->x = fabs(1 / ray->x);
// 	if (ray->x == 0)
// 		deltaDist->y = 1e30;
// 	else
// 		deltaDist->y = fabs(1 / ray->y);
// }

// t_vector	calc_side(t_vector *step, t_vector deltaDist, t_player *player, t_vector *ray)
// {
// 	t_vector	pos;
// 	t_vector	sideDist;

// 	pos.x = player->x;
// 	pos.y = player->y;
// 	step->x = 1;
// 	step->y = 1;
// 	sideDist.x = ((int)pos.x + 1.0 - pos.x) * deltaDist.x;
// 	sideDist.y = ((int)pos.y + 1.0 - pos.y) * deltaDist.y;
// 	if (ray->x < 0)
// 	{
// 		step->x = -1;
// 		sideDist.x = (pos.x - (int)pos.x) * deltaDist.x;
// 	}
// 	if (ray->y < 0)
// 	{
// 		step->y = -1;
// 		sideDist.y = (pos.y - (int)pos.y) * deltaDist.y;
// 	}
// 	return (sideDist);
// }

// t_vector	is_hit(t_gen *gen, t_vector deltaDist, t_vector sideDist, t_vector step)
// {
// 	t_vector	pos;
// 	t_vector	ray;

// 	pos.x = (int)gen->player.x;
// 	pos.y = (int)gen->player.y;
// 	while (worldMap[(int)pos.x][(int)pos.y] > 0)
// 	{
// 		if (sideDist.x < sideDist.y)
// 		{
// 			sideDist.x += deltaDist.x;
// 			pos.x += step.x;
// 		}
// 		else
// 		{
// 			sideDist.y += deltaDist.y;
// 			pos.y += step.y;
// 		}
// 	}
// 	ray.x = sideDist.x;
// 	ray.y = sideDist.y;
// 	return (ray);
// }

// void	calculate_ray(t_gen *gen, t_vector *ray, int x)
// {
// 	t_vector	sideDist;
// 	t_vector	deltaDist;
// 	t_vector	step;
// 	double		cameraX;

// 	cameraX = 2 * x / (double)WIDTH - 1;
// 	ray->x = gen->player.dirX +  gen->player.planeX * cameraX;
// 	ray->y = gen->player.dirY +  gen->player.planeY * cameraX;
// 	calc_delta(&deltaDist, ray);
// 	sideDist = calc_side(&step, deltaDist, &gen->player, ray);
// 	*ray = is_hit(gen, deltaDist, sideDist, step);
// }

// void	draw2dray(t_gen *gen, int color)
// {
// 	t_vector	ray;
// 	int			x;

// 	x = -1;
// 	++color;
// 	while (++x < WIDTH)
// 	{
// 		calculate_ray(gen, &ray, x);
// 		printf("ray.x: %f\n", ray.x);
// 		printf("ray.y: %f\n", ray.y);
// 	}
// }

// void	render_screen(void *param)
// {
// 	t_gen	*gen;

// 	gen = (t_gen *)param;
// 	draw2dray(gen, 0x00FF00);
// 	mlx_image_to_window(gen->mlx, gen->win, 0, 0);
// }

// void	clear_screen(t_gen *gen, int color)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < HEIGHT)
// 	{
// 		j = -1;
// 		while (++j < WIDTH)
// 			mlx_put_pixel(gen->win, j, i, color);
// 	}
// }

void	draw_square(mlx_t *mlx, int x, int y, int color)
{
	int			i;
	int			j;
	mlx_img_t	*img;

	i = 0;
	img = mlx_new_image(mlx, SIZE / 4, SIZE / 4);
	memset(img->pixels, color, img->width * img->height * sizeof(int32_t));
	mlx_imaget_to_window(mlx, img, x * SIZE, y * SIZE);
	mlx_delete_image(mlx, img);
}

void drawMap2D(t_gen *gen)
{
	int			x;
	int			y;
	int			color;

	y = -1;
	while (++y < mapY)
	{
		x = -1;
		while (++x < mapX)
		{
			if (map[y][x] > 0)
				color = 0xFFFFFF;
			else
				color = 0x000000;
			draw_square(gen->mlx, x, y, color);
		} 
	}
	mlx_image_to_window(gen->mlx, gen->player.img, gen->player.x * SIZE, gen->player.y * SIZE);
}

int	main(void)
{
	mlx_t	*mlx;
	t_gen	gen;

	mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!mlx)
		return (EXIT_FAILURE);
	init_gen(&gen, mlx);
	// clear_screen(&gen, 0x000000);
	drawMap2D(&gen);
	mlx_loop_hook(mlx, render_screen, &gen);
	mlx_key_hook(mlx, movement, &gen);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
