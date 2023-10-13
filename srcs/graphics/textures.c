/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 15:54:26 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/13 13:22:08 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "cub3d.h"

static void	get_texture(t_gen *gen, t_ray *ray)
{
	if (ray->side == 0 && ray->raydir_x > 0)
		gen->txtrs.t_text = gen->txtrs.t_ea;
	else if (ray->side == 0 && ray->raydir_x < 0)
		gen->txtrs.t_text = gen->txtrs.t_we;
	else if (ray->side == 1 && ray->raydir_y > 0)
		gen->txtrs.t_text = gen->txtrs.t_so;
	else
		gen->txtrs.t_text = gen->txtrs.t_no;
}

static int	get_color_textures(t_gen *gen, int x, int y)
{
	uint8_t			*pixel;
	mlx_texture_t	*text;

	text = gen->txtrs.t_text;
	pixel = &text->pixels[(text->width * y + x) * text->bytes_per_pixel];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

void	draw_pixels(t_gen *gen, t_ray *ray, int x)
{
	int		text_y;
	int		text_x;
	double	step;
	double	text_pos;

	get_texture(gen, ray);
	text_x = (int)((1 - ray->wall_x) * (double)(gen->txtrs.t_text->width));
	if (ray->side == 0 && ray->raydir_x > 0)
		text_x = gen->txtrs.t_text->width - text_x - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		text_x = gen->txtrs.t_text->width - text_x - 1;
	step = 1.0 * (int)gen->txtrs.t_text->height / ray->height;
	text_pos = (ray->start - (int)HEIGHT / 2 + ray->height / 2) * step;
	while (ray->start < ray->end)
	{
		text_y = (int)text_pos & (gen->txtrs.t_text->height - 1);
		text_pos += step;
		ray->color = get_color_textures(gen, text_x, text_y);
		mlx_put_pixel(gen->win, WIDTH - x, ray->start, ray->color);
		++ray->start;
	}
}
