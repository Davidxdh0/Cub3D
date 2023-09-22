/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 23:10:47 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/22 23:27:22 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>

#define WIDTH 512
#define HEIGHT 512

int32_t mlx_main(void);
void 	ft_hook(void* param);
void 	ft_randomize(void* param);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

#endif