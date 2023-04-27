/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:36:39 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/26 13:02:58 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_facing_up(float angle)
{
	return (angle > M_PI);
}

int	is_facing_left(float angle)
{
	return (angle > M_PI_2 && angle < 3 * M_PI_2);
}

void	draw_ray(t_var *data, t_ray *ray)
{
	float	x;
	float	y;

	x = ray->x;
	y = ray->y;
	while (data->map[(int)y / (WINDOW_HEIGHT / MAP_HEIGHT)]
		[(int)x / (WINDOW_WIDTH / MAP_WIDTH)] != '1')
	{
		x += ray->dx;
		y += ray->dy;
		my_mlx_pixel_put(&data->img, to_minmap(x, 0),
			to_minmap(y, 1), 0x00FF0000);
	}
	// t_point wall;
	// wall = point_wall(data, ray);
	// for (int i=0; i < 4; i++)
	// {
	// 	my_mlx_pixel_put(&data->img, to_minmap(wall.x, 0),
	// 		to_minmap(wall.y, 1), 0x00FFFF00);
	// 	wall.x += ray->dx;
	// 	wall.y += ray->dy;
	// }
}

void	draw_rays(t_var *data)
{
	int		i;
	t_ray	ray;

	i = 0;
	while (data->player.angle - (FOV / 2) + 0.01 * i
		< data->player.angle + (FOV / 2))
	{
		ray.x = data->player.x + 4;
		ray.y = data->player.y + 4;
		ray.angle = data->player.angle - (FOV / 2) + 0.01 * i;
		ray.dx = cos(ray.angle);
		ray.dy = sin(ray.angle);
		draw_ray(data, &ray);
		i++;
	}
	// distances_walls(data);
}
