/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/07 19:56:15 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/13 17:10:03 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cub3D.h"

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

typedef struct s_bres
{
	double	dx;
	double	dy;
	double	sx;
	double	sy;
	double	err;
	double	err2;
}				t_bres;

//minimap.c
void	draw_minimap(t_gen *gen);
void	bresenham(t_gen *gen, int *pos, int *line);
void	draw_vision(t_gen *gen, t_player *player, t_ray ray);
void	draw_background(t_gen *gen);

//raycasting.c
void	cast_ray(t_gen *gen, t_player *player, int x);
void	calc_wall_dist(t_gen *gen, t_ray *ray);
void	calc_side_dist(t_player *player, t_ray *ray);
void	render_screen(void *param);

//textures.c
void	draw_pixels(t_gen *gen, t_ray *ray, int x);

#endif
