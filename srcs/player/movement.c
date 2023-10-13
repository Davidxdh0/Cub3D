/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 13:31:30 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/13 13:15:50 by dyeboa        ########   odam.nl         */
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
	if(gen->map[(int)(player->y)][(int)(player->x + ray.raydir_x * 0.5)] == '1' && fabs(ray.walldist) < 0.2)
		return (0);
	if(gen->map[(int)(player->y + ray.raydir_y * 0.5)][(int)(player->x)] == '1' && fabs(ray.walldist) < 0.2)
		return (0);
	if(gen->map[(int)(player->y + ray.raydir_y * 0.5)][(int)(player->x + ray.raydir_x * 0.5)] == '1' && fabs(ray.walldist) < 0.2)
		return (0);
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
		walk_right(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_D))
		walk_left(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_LEFT))
		rotate_right(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_RIGHT))
		rotate_left(gen);
	mlx_mouse_hook(gen->mlx, &clicking, gen);
	if (gen->draw == 1)
		render_screen(gen);
}

void	scrolling(double xdelta, double ydelta, void *param)
{
	t_gen	*gen;

	gen = (t_gen *)param;
	if (ydelta > 0)
	{
		// printf("Scrolling up %d\n", gen->random);
		rotate_left(gen);
		if (gen->random == 0)
			gen->draw = 1;
		gen->random = 1;
	}
	else if (ydelta < 0)
	{
		// printf("Scrolling down\n");
		rotate_right(gen);
		if (gen->random == 1)
			gen->draw = 1;
		gen->random = 0;
	}
	if (xdelta < 0)
		puts("FFFFFFF");
}

//check if there is a door in front of the player / in what direction it is facing
void	door_key(t_gen *gen, int key)
{
	int		x;
	int		y;
	char	**map;
	
	x = (int)round(gen->player.x + gen->player.dir_x);
	y = (int)round(gen->player.y + gen->player.dir_y);
	map = gen->map;
	if (x == (int)gen->player.x && y == (int)gen->player.y)
		return ;
	if (map[y][x] == 'l' && key == 0)
		map[y][x] = 'c';
	else if (map[y][x] == 'c' && key == 1)
		map[y][x] = 'l';
}

void	clicking(mouse_key_t but, action_t act, modifier_key_t mods, void *par)
{
	t_gen	*gen;

	(void)mods;
	gen = (t_gen *)par;
	if (but == 0 && act == 1)
	{
		door_key(gen, 1);
		gen->draw = 1;
	}
	else if (but == 1 && act == 1)
	{
		door_key(gen, 0);
		gen->draw = 1;
	}
}
