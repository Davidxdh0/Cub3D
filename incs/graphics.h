/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/07 19:56:15 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/10 18:05:40 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cub3d.h"

typedef struct s_ray
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	walldist;
	double	map_x;
	double	map_y;
	double	wall_x;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		height;
	int		start;
	int		end;
	int		color;
}			t_ray;

typedef struct s_sprite
{
	int		order[1024];
	double	zdist[1024];
	double	x;
	double	y;
	double	dist;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		height;
	int		width;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		tex_x;
	int		tex_y;
	int		color;
}			t_sprite;

//minimap.c
void	draw_minimap(t_gen *gen);
// void	bresenham(t_gen *gen, t_vector *cur, t_vector *end);
void	bresenham(t_gen *gen, int x1, int y1, int x2, int y2);
void	draw_vision(t_gen *gen, t_player *player, t_ray ray);
void	draw_background(t_gen *gen);

//raycasting.c
void	cast_ray(t_gen *gen, t_player *player, int x, double *zbuffer);
void	calc_wall_dist(t_gen *gen, t_ray *ray);
void	calc_side_dist(t_player *player, t_ray *ray);
void	render_screen(void *param);

//textures.c
void	draw_pixels(t_gen *gen, t_ray *ray, int x);

#endif
