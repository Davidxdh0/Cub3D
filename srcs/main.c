#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <math.h>
#include "cub3d.h"


int map[MAP_WIDTH][MAP_HEIGHT] = \
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,0,0,0,0,1,3,3,3,3,3,3,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,0,0,0,0,0,3,3,3,3,3,3,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,0,0,0,0,0,1,1,1,3,3,3,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,1},
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
	int		x;

	gen = (t_gen *)param;
	x = 0;
	memset(gen->win->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	while (x < WIDTH)
	{
		cast_ray(gen, &gen->player, x);
		++x;
	}
	mlx_image_to_window(gen->mlx, gen->win, 0, 0);
}

int **create_map(void)
{
	int	**my_map;
	int	i;
	int	j;

	my_map = malloc(sizeof(int *) * MAP_HEIGHT);
	if (!my_map)
		return (NULL);
	i = 0;
	while (i < MAP_HEIGHT)
	{
		my_map[i] = malloc(sizeof(int) * MAP_WIDTH);
		if (!my_map[i])
			return (NULL);
		j = 0;
		while (j < MAP_WIDTH)
		{
			my_map[i][j] = map[i][j];
			++j;
		}
		++i;
	}
	return (my_map);
}

void	init_gen(t_gen *gen, mlx_t *mlx)
{
	gen->mlx = mlx;
	gen->map = create_map();
	gen->win = mlx_new_image(mlx, WIDTH, HEIGHT);
	gen->player.x = 12;
	gen->player.y = 22;
	gen->player.dir_x = -1;
	gen->player.dir_y = 0;
	gen->player.plane_x = 0;
	gen->player.plane_y = 0.66;
	gen->player.img = mlx_new_image(mlx, SIZE / 8, SIZE / 8);
	for (int i = 0; i < SIZE / 8; i++)
		for (int j = 0; j < SIZE / 8; j++)
				mlx_put_pixel(gen->player.img, i, j, 0xFF00FFFF);
	mlx_image_to_window(gen->mlx, gen->player.img, gen->player.x * SIZE / 4, gen->player.y * SIZE / 4);
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
