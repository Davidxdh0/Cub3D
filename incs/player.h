/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/07 19:33:21 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/09 19:49:31 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

//player.c
void	init_player(t_gen *gen, mlx_t *mlx, t_map *cmap);
void	movement(void *param);
void	rotate(mlx_key_data_t data, t_gen *gen);
void	walk(mlx_key_data_t data, t_gen *gen);

//keys.c
void	close_escape(t_gen *gen);
void	rotate_right(t_gen *gen);
void	rotate_left(t_gen *gen);
void	walk_forwards(t_gen *gen);
void	walk_backwards(t_gen *gen);
void	walk_left(t_gen *gen);
void	walk_right(t_gen *gen);

//collision
// int		can_move_y(t_gen *gen, int speed);
// int		can_move_x(t_gen *gen, int speed);
int		can_move(t_gen *gen, int xspeed, int yspeed);

//mouse
void	scrolling(double xdelta, double ydelta, void *param);
void	clicking(mouse_key_t but, action_t act, modifier_key_t mods, void *par);
#endif