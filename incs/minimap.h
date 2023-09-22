/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 23:10:47 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/22 23:12:02 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

#include "libft.h"
#include <stdio.h> // printf
#include <fcntl.h> // open
#include <stdlib.h> // exit
#include <stdbool.h> // bool

#define WIDTH 512
#define HEIGHT 512

int32_t mlx_init(int32_t argc, const char* argv[]);
void ft_hook(void* param);
void ft_randomize(void* param);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

#endif