/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/07 19:33:21 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/13 17:10:13 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3D.h"

//init.c
void	init_player(t_gen *gen, mlx_t *mlx, t_map *cmap);

//player.c
int		can_move(t_gen *gen, int xspeed, int yspeed);
void	movement(void *param);

//keys.c - keys2.c
void	close_escape(t_gen *gen);
void	rotate_right(t_gen *gen);
void	rotate_left(t_gen *gen);
void	walk_forwards(t_gen *gen);
void	walk_backwards(t_gen *gen);
void	walk_left(t_gen *gen);
void	walk_right(t_gen *gen);
void	rotate(mlx_key_data_t data, t_gen *gen);
void	walk(mlx_key_data_t data, t_gen *gen);

//mouse.c
void	door_key(t_gen *gen, int key);
void	scrolling(double xdelta, double ydelta, void *param);
void	clicking(mouse_key_t but, action_t act, modifier_key_t mods, void *par);
#endif