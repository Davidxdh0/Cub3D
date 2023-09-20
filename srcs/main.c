#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <math.h>
#include "cub3d.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define WIDTH 800
#define HEIGHT 600

int worldMap[MAP_WIDTH][MAP_HEIGHT] = \
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	calc_height(t_vector delta, t_vector side, int wall)
{
	int			line_height;
	double		wall_dist;

	if (wall == 0)
		wall_dist = side.x - delta.x;
	else
		wall_dist = side.y - delta.y;
	line_height = (int)(HEIGHT / wall_dist);
	printf("line_height = %d\n", line_height);
	return (line_height);
}

int	dda(t_vector delta, t_vector step, t_vector side_dist, t_gen *gen)
{
	int			side;
	t_vector	map_pos;
	int			hit;

	hit = 0;
	map_pos.x = (int)gen->player.pos.x;
	map_pos.y = (int)gen->player.pos.y;
	while (hit == 0)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta.x;
			map_pos.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta.y;
			map_pos.y += step.y;
			side = 1;
		}
		if (worldMap[(int)map_pos.x][(int)map_pos.y] > 0)
			hit = 1;
	}
	return (calc_height(delta, side_dist, side));
}

int	calc_side(t_vector ray, t_vector delta, t_vector map_pos, t_gen *gen)
{
	t_vector	step;
	t_vector	side_dist;

	step.y = 1;
	step.x = 1;
	if (ray.x < 0)
	{
		step.x = -1;
		side_dist.x = (gen->player.pos.x - map_pos.x) * delta.x;
	}
	else
		side_dist.x = (map_pos.x + 1.0 - gen->player.pos.x) * delta.x;
	if (ray.y < 0)
	{
		step.y = -1;
		side_dist.y = (gen->player.pos.y - map_pos.y) * delta.y;
	}
	else
		side_dist.y = (map_pos.y + 1.0 - gen->player.pos.y) * delta.y;
	return (dda(delta, step, side_dist, gen));
}

int	calc_delta(t_vector ray, t_gen *gen)
{
	t_vector	delta_dist;
	t_vector	map_pos;

	map_pos.x = (int)gen->player.pos.x;
	map_pos.y = (int)gen->player.pos.y;
	if (ray.x == 0)
		delta_dist.x = 1e30 ;
	else
		delta_dist.x = fabs(1 / ray.x);
	if (ray.y == 0)
		delta_dist.y = 1e30 ;
	else
		delta_dist.y = fabs(1 / ray.y);
	return (calc_side(ray, delta_dist, map_pos, gen));
}

void	draw_line(int x, mlx_image_t *win, int line_height)
{
	int	start;
	int	end;
	int	i;
	int	color;

	start = -line_height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	i = 0;
	color = 0xFFFFFF;
	while (i < start)
		mlx_put_pixel(win, x, i++, 0x000000FF);
	while (i < end)
		mlx_put_pixel(win, x, i++, color);
	while (i < HEIGHT)
		mlx_put_pixel(win, x, i++, 0x000000FF);
}

void	render_screen(void *param)
{
	t_gen		*gen;
	t_vector	ray;
	int			cam_x;
	int			x;
	int			line_height;

	gen = (t_gen *)param;
	x = 0;
	while (x < WIDTH)
	{
		cam_x = 2 * x / (double)WIDTH - 1;
		ray.x = gen->player.dir.x + gen->player.plane.x * cam_x;
		ray.y = gen->player.dir.y + gen->player.plane.y * cam_x;
		line_height = calc_delta(ray, gen);
		draw_line(x, gen->win, line_height);
		++x;
	}
	mlx_image_to_window(gen->mlx, gen->win, 0, 0);
}

void	init_gen(t_gen *gen, mlx_t *mlx)
{
	gen->mlx = mlx;
	gen->player.pos.x = 2;
	gen->player.pos.y = 2;
	gen->player.dir.x = -1;
	gen->player.dir.y = 0;
	gen->player.plane.x = 0;
	gen->player.plane.y = 0.66;
	gen->win = mlx_new_image(mlx, WIDTH, HEIGHT);
}

void	ft_hook(mlx_key_data_t key, void *param)
{
	t_gen	*gen;

	gen = (t_gen *)param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(gen->mlx);
	if (key.key == MLX_KEY_UP && key.action == MLX_PRESS)
	{
		if (worldMap[(int)(gen->player.pos.x + gen->player.dir.x * 2)] \
		[(int)gen->player.pos.y] == false)
			gen->player.pos.x += gen->player.dir.x * 2;
		if (worldMap[(int)gen->player.pos.x] \
		[(int)(gen->player.pos.x + gen->player.dir.x * 2)] == false)
			gen->player.pos.y += gen->player.dir.y * 2;
	}
	if (key.key == MLX_KEY_DOWN && key.action == MLX_PRESS)
	{
		if (worldMap[(int)(gen->player.pos.x + gen->player.dir.x * 2)] \
		[(int)gen->player.pos.y] == false)
			gen->player.pos.x -= gen->player.dir.x * 2;
		if (worldMap[(int)gen->player.pos.x] \
		[(int)(gen->player.pos.x + gen->player.dir.x * 2)] == false)
			gen->player.pos.y -= gen->player.dir.y * 2;
	}
	if (key.key == MLX_KEY_LEFT)
	{
		double oldDirX = gen->player.dir.x;
		gen->player.dir.x = gen->player.dir.x * cos(2) - gen->player.dir.y * sin(2);
		gen->player.dir.y = oldDirX * sin(2) + gen->player.dir.y * cos(2);
		double oldPlaneX = gen->player.plane.x;
		gen->player.plane.x = gen->player.plane.x * cos(2) - gen->player.plane.y * sin(2);
		gen->player.plane.y = oldPlaneX * sin(2) + gen->player.plane.y * cos(2);
	}
	if (key.key == MLX_KEY_RIGHT)
	{
		double oldDirX = gen->player.dir.x;
		gen->player.dir.x = gen->player.dir.x * cos(-2) - gen->player.dir.y * sin(-2);
		gen->player.dir.y = oldDirX * sin(-2) + gen->player.dir.y * cos(-2);
		double oldPlaneX = gen->player.plane.x ;
		gen->player.plane.x  = gen->player.plane.x  * cos(-2) - gen->player.plane.y * sin(-2);
		gen->player.plane.y = oldPlaneX * sin(-2) + gen->player.plane.y * cos(-2);
	}
}

int	main(void)
{
	mlx_t	*mlx;
	t_gen	gen;

	mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!mlx)
		return (EXIT_FAILURE);
	init_gen(&gen, mlx);
	mlx_loop_hook(mlx, render_screen, &gen);
	mlx_key_hook(mlx, ft_hook, &gen);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
