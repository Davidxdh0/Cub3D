/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 13:31:30 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/09 23:29:02 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "graphics.h"
#include "cub3d.h"


// printf("x y [%f][%f]\n", player->x, player->y);
// printf("walldist %f fabs %f, side %d [%d][%d] || [%d][%d]\n", ray.walldist, fabs(ray.walldist), ray.side, (int)(player->y), (int)(player->x + ray.raydir_x * 0.5), (int)(player->y + ray.raydir_y * 0.5), (int)(player->x));
// printf("ray->sidedist_x < ray->sidedist_y, %f %f\n", ray.sidedist_x, ray.sidedist_y);
// printf("ray.deltadist_x  ray.deltadist_y %f %f\n", ray.deltadist_x, ray.deltadist_y);
// printf("ray.raydirx  ray.raydiry %f %f\n", ray.raydir_x, ray.raydir_y);
// printf("ray.map x y  %f %f\n", ray.map_x , ray.map_y);
int	can_move(t_gen *gen, int xspeed, int yspeed)
{
	t_ray		ray;
	t_player	*player;
	float		move;

	move = gen->mlx->delta_time * 5.0;
	player = &gen->player;
	ray.camera_x = 2 * (HEIGHT / 2) / (WIDTH - 1);
	ray.raydir_x = (player->dir_x + player->plane_x * ray.camera_x) * xspeed;
	ray.raydir_y = (player->dir_y + player->plane_y * ray.camera_x) * yspeed;
	ray.map_x = (int)(player->x);
	ray.map_y = (int)(player->y);
	ray.deltadist_x = 1e30;
	ray.deltadist_y = 1e30;
	ray.side = 0;
	calc_side_dist(player, &ray);
	calc_wall_dist(gen, &ray);
	if (ray.side == 0)
		ray.walldist = ray.sidedist_x - ray.deltadist_x;
	else
		ray.walldist = ray.sidedist_y - ray.deltadist_y;
	(void)xspeed;
	(void)yspeed;
	
	if(gen->map[(int)(player->y)][(int)(player->x + ray.raydir_x * 0.5)] == '1' && fabs(ray.walldist) < 0.5)
		return (0);
    if(gen->map[(int)(player->y + ray.raydir_y * 0.5)][(int)(player->x)] == '1' && fabs(ray.walldist) < 0.5)
		return (0);
	if(gen->map[(int)(player->y + ray.raydir_y * 0.5)][(int)(player->x + ray.raydir_x * 0.5)] == '1' && fabs(ray.walldist) < 0.8)
		return (0);

	if (player->dir_y > 0)
	{
		if(gen->map[(int)(player->y + 1)][(int)(player->x  + ray.raydir_x * move)] == '1' && fabs(ray.walldist) < 0.5)
			return (0);
		if(gen->map[(int)(player->y + 1 + ray.raydir_y * move)][(int)(player->x )] == '1' && fabs(ray.walldist) < 0.5)
			return (0);
	}
	return (1);
}

// int	can_move_x(t_gen *gen, int speed)
// {
// 	double	x;
// 	double	y;
// 	double	diff;

// 	x = (gen->player.x) + (speed * gen->player.dir_x);
// 	y = (gen->player.y);
// 	if (x < 1 || x > gen->width - 1.5 || y < 1 || y > gen->height - 1)
// 		return (0);
// 	//if (gen->map[(int)round(y)][(int)round(x)] == '1' 
// 	// || gen->map[(int)round(y)][(int)round(x - 1)] == '1' 
// 	// || gen->map[(int)round(y - 1)][(int)round(x)] == '1' 
// 	// || gen->map[(int)round(y - 1)][(int)round(x) - 1] == '1')
// 	if (gen->map[(int)round(y)][(int)round(x)] == '1')
// 	{
// 		diff = round(x);
// 		if (fabs(x - diff) < 0.5)
// 			return (0);
// 	}
// 	return (1);
// }

// int	can_move_y(t_gen *gen, int speed)
// {
// 	double	x;
// 	double	y;
// 	double	diff;

// 	x = (gen->player.x);
// 	y = (gen->player.y) + (speed * gen->player.dir_y);
// 	if (x < 1.5 || x > gen->width - 1.5 || y < 1.5 || y > gen->height - 1)
// 		return (0);
// 	//if (gen->map[(int)round(y)][(int)round(x)] == '1') 
// 	// || gen->map[(int)round(y - 1)][(int)round(x)] == '1' 
// 	// || gen->map[(int)round(y)][(int)round(x - 1)] == '1' 
// 	// || gen->map[(int)round(y - 1)][(int)round(x - 1)] == '1')
// 	if (gen->map[(int)round(y)][(int)round(x)] == '1')
// 	{
// 		diff = round(y);
// 		if (fabs(y - diff) < 0.5)
// 			return (0);
// 	}
// 	return (1);
// }

void	movement(void *param)
{
	t_gen	*gen;

	gen = (t_gen *)param;
	mlx_scroll_hook(gen->mlx, &scrolling, gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_ESCAPE))
		close_escape(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_W))
		walk_forwards(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_S))
		walk_backwards(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_A))
		walk_left(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_D))
		walk_right(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_LEFT))
		rotate_left(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_RIGHT))
		rotate_right(gen);
	mlx_mouse_hook(gen->mlx, &clicking, gen);
	if (gen->draw == 1)
	{
		render_screen(gen);
		gen->draw = 0;
	}
}

void	scrolling(double xdelta, double ydelta, void *param)
{
	t_gen	*gen;

	gen = (t_gen *)param;
	if (ydelta > 0)
	{
		printf("Scrolling up %d\n", gen->random);
		if (gen->random == 0)
			gen->draw = 1;
		gen->random = 1;
	}
	else if (ydelta < 0)
	{
		printf("Scrolling down\n");
		if (gen->random == 1)
			gen->draw = 1;
		gen->random = 0;
	}
	if (xdelta < 0)
		puts("FFFFFFF");
}

void	clicking(mouse_key_t but, action_t act, modifier_key_t mods, void *par)
{
	t_gen	*gen;

	gen = (t_gen *)par;
	if (but == 0 && act == 1)
	{
		printf("Clicked left button, opens doors\n");
		door_key(gen->map, 1);
		gen->draw = 1;
	}
	else if (but == 1 && act == 1)
	{
		printf("Clicked right button, closes doors\n");
		door_key(gen->map, 0);
		gen->draw = 1;
	}
	else if (mods == 0x0002)
		printf("You pressed control, well done!\n");
}

void	door_key(char **array, int key)
{
	int	x;
	int	y;

	y = 0;
	while (array[y])
	{
		x = 0;
		while (array[y][x])
		{
			if (array[y][x] == 'l' && key == 1)
				array[y][x] = 'c';
			if (array[y][x] == 'c' && key == 0)
				array[y][x] = 'l';
			x++;
		}
		y++;
	}
}
