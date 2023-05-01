/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 22:13:38 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/01 16:05:16 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_color(t_point wall, t_point p, t_texture texture)
{
	int		x_ratio;
	int		y_ratio;
	t_point	result;

	x_ratio = texture.width / wall.x;
	y_ratio = texture.height / wall.y;
	result.x = (int)(p.x * x_ratio);
	result.y = (int)(p.y * y_ratio);
	// printf("texture width: %d\n", texture.width);
	return (texture.data[((int)result.y * texture.width + (int)result.x)]);
}

int	get_wall_color(t_var *data, t_ray ray, int y, int wall_height)
{
	t_point	point;
	t_point	wall;

	wall.y = wall_height;
	point.y = y;
	if (ray.type == 'D' || ray.type == 'U')
	{
		
		wall.x = (WINDOW_WIDTH / MAP_WIDTH);
		point.x = (int)ray.wall.x % (WINDOW_WIDTH / MAP_WIDTH);
	}
	else
	{
		wall.x = (WINDOW_HEIGHT / MAP_HEIGHT);
		point.x = (int)ray.wall.y % (WINDOW_HEIGHT / MAP_HEIGHT);
	}
	// if (ray.type == 'D')
		return (get_texture_color(wall, point, data->textures.north));
	// else if (ray.type == 'U')
	// 	get_texture_color(wall, result, data->textures.north);
	// else if (ray.type == 'L')
	// 	get_texture_color(wall, result, data->textures.west);
	// else if (ray.type == 'R')
	// 	get_texture_color(wall, result, data->textures.east);
	return (0);
}
