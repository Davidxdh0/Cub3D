/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 17:54:13 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/10 17:56:33 by bfranco       ########   odam.nl         */
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