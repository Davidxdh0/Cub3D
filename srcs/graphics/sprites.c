/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 17:54:13 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/10 21:34:54 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "graphics.h"

/*
	1. Make a list of sprites at startup

	2. Sort the sprites from far to close
	
	3. Perform transformation to avoid fisheye

	4. Calculate the height of the sprite on the screen

	5. Calculate the width of the sprite on the screen

	6. Draw the sprite stripe by stripe
*/

// sprites pointer is an array of sprites, just save x and y of map at th beginning
render_sprites(t_gen *gen, t_sprite *sprites)
{
	t_sprite	sprite;
	int			i;
	int			posx;
	int			posy;

	posx = gen->player.x;
	posy = gen->player.y;
	i = 0;
    while (i < 2)
    {
      sprite.order[i] = i;
      sprite.zdist[i] = ((posx - sprites[i].x) * (posx - sprites[i].x) \
	  + (posy - sprites[i].y) * (posy - sprites[i].y));
	  i++;
	}
    sortSprites(sprite.order, sprite.zdist, i);

}
void	sortSprites(int *order, double *dist, int amount)