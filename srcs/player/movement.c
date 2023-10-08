/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 13:31:30 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/08 15:57:51 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "graphics.h"
#include "cub3d.h"

int	can_move(t_gen *gen, int xspeed, int yspeed)
{
	t_ray		ray;
	t_player	*player;

	player = &gen->player;
	ray.camera_x = 2 * (WIDTH / 2) / (HEIGHT - 1);
	ray.raydir_x = (player->dir_x + player->plane_x * ray.camera_x) * xspeed;
	ray.raydir_y = (player->dir_y + player->plane_y * ray.camera_x) * yspeed;
	ray.map_x = (int)player->x;
	ray.map_y = (int)player->y;
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
	if (gen->draw == 1)
	{
		render_screen(gen);
		gen->draw = 0;
	}
}

// void	scrolling(void *param)
// {
// 	t_gen	*gen;
// 	double x;
// 	double y;
// 	gen = (t_gen *)param;
// 	if (mlx_scroll_hook(gen->mlx, MLX_KEY_ESCAPE))
// 		close_escape(gen);
// }