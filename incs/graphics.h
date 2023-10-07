/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/07 19:56:15 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/07 20:24:53 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cub3d.h"

//minimap.c
void	draw_minimap(t_gen *gen);
// void	bresenham(t_gen *gen, t_vector *cur, t_vector *end);
void	bresenham(t_gen *gen, int x1, int y1, int x2, int y2);
void	draw_vision(t_gen *gen, t_player *player, t_ray ray);
void	draw_background(t_gen *gen);

//raycasting.c
void	cast_ray(t_gen *gen, t_player *player, int x);
void	render_screen(void *param);

//textures.c
void	draw_pixels(t_gen *gen, t_ray *ray, int x);

#endif
