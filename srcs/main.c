#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <math.h>
#include "cub3d.h"

int32_t get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void bresenham(t_gen *gen, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;

	dx = abs(x2 - x1);
	dy = -abs(y2 - y1);
	sx = 1;
	if (x1 > x2)
		sx = -1;
	sy = 1;
	if (y1 > y2)
		sy = -1;
	err = dx + dy;
	while (x1 != x2 && y1 != y2)
	{
		mlx_put_pixel(gen->win, x1, y1, 0xFF0000FF);
		err2 = 2 * err;
		if (err2 >= dy && x1 != x2)
		{
			err += dy;
			x1 += sx;
		}
		if (err2 <= dx && y1 != y2)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	render_screen(void *param)
{
	t_gen	*gen;

	gen = (t_gen *)param;
	memset(gen->win->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	bresenham(gen, gen->player.x * (SIZE / 2), gen->player.y * (SIZE / 2), SIZE / 2, SIZE / 2);
	mlx_image_to_window(gen->mlx, gen->win, 0, 0);
}

void	init_gen(t_gen *gen, mlx_t *mlx)
{
	gen->mlx = mlx;
	gen->win = mlx_new_image(mlx, WIDTH, HEIGHT);
	gen->player.x = 20;
	gen->player.y = 10;
	gen->player.dirX = -1;
	gen->player.dirY = 1;
	gen->player.planeX = 0;
	gen->player.planeY = 0.66;
	gen->player.img = mlx_new_image(mlx, SIZE / 8, SIZE / 8);
	// int color = get_rgba(0xFF, 0xFF, 0xFF, 0xFF);
	for (int i = 0; i < SIZE / 8; i++)
		for (int j = 0; j < SIZE / 8; j++)
				mlx_put_pixel(gen->player.img, i, j, 0xFF00FFFF);
	mlx_image_to_window(gen->mlx, gen->player.img, gen->player.x * SIZE / 2, gen->player.y * SIZE / 2);
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
	// memset(gen.win->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));
	drawMap2D(&gen);
	mlx_loop_hook(mlx, render_screen, &gen);
	mlx_key_hook(mlx, movement, &gen);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
