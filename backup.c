// void	draw_vert_line(t_gen *gen, t_ray *ray, int x)
// {
// 	if (ray->side == 0)
// 		ray->walldist = ray->sidedist_x - ray->deltadist_x;
// 	else
// 		ray->walldist = ray->sidedist_y - ray->deltadist_y;
// 	ray->height = (int)(HEIGHT / ray->walldist);
// 	ray->start = -ray->height / 2 + HEIGHT / 2;
// 	ray->end = ray->height / 2 + HEIGHT / 2;
// 	if (ray->start < 0)
// 		ray->start = 0;
// 	if (ray->end >= HEIGHT)
// 		ray->end = HEIGHT - 1;
// 	if (ray->side == 1)
// 		ray->color = get_color(gen->map[(int)ray->map_y][(int)ray->map_x]);
// 	else
// 		ray->color = get_color(gen->map[(int)ray->map_y][(int)ray->map_x]) / 2;
// 	while (ray->start < ray->end)
// 	{
// 		mlx_put_pixel(gen->win, WIDTH - x, ray->start, ray->color);
// 		++ray->start;
// 	}
// }