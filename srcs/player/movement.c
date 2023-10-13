/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 13:31:30 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/13 13:41:26 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "graphics.h"
#include "cub3d.h"

static int	check_move(t_gen *gen, t_player *p, t_ray ray)
{
	if (!is_walkable(gen->map[(int)(p->y)][(int)(p->x + ray.raydir_x * 0.5)]) \
		&& fabs(ray.walldist) < 0.4)
		return (0);
	if (!is_walkable(gen->map[(int)(p->y + ray.raydir_y * 0.5)][(int)(p->x)]) \
		&& fabs(ray.walldist) < 0.4)
		return (0);
	if (!is_walkable(gen->map[(int)(p->y + ray.raydir_y * 0.5)] \
		[(int)(p->x + ray.raydir_x * 0.5)]) && fabs(ray.walldist) < 0.4)
		return (0);
	return (1);
}

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
	return (check_move(gen, player, ray));
}

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
