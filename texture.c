/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 22:13:38 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/01 23:35:09 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	get_texture(t_var *data, t_ray ray)
{
	if (ray.type == 'D')
		return (data->textures.south);
	else if (ray.type == 'U')
		return (data->textures.north);
	else if (ray.type == 'L')
		return (data->textures.west);
	else if (ray.type == 'R')
		return (data->textures.east);
	else
		return (data->textures.south);
}

int	get_position_texture(t_var *data, t_ray ray)
{
	double		block_x;
	double		ratio;
	t_texture	texture;

	texture = get_texture(data, ray);
	if (ray.type == 'D' || ray.type == 'U')
	{
		block_x = fmod(ray.wall.x, (double)WINDOW_WIDTH / MAP_WIDTH);
		ratio = (double)texture.width / (WINDOW_WIDTH / MAP_WIDTH);
		if (ray.type == 'U')
			block_x = (double)WINDOW_WIDTH / MAP_WIDTH - block_x;
	}
	else
	{
		block_x = fmod(ray.wall.y, (double)WINDOW_HEIGHT / MAP_HEIGHT);
		ratio = (double)texture.width / ((double)WINDOW_HEIGHT / MAP_HEIGHT);
		if (ray.type == 'L')
			block_x = (double)WINDOW_HEIGHT / MAP_HEIGHT - block_x;
	}
	return ((block_x * ratio));
}

int	get_wall_color(t_var *data, t_ray ray, int y, int wall_height)
{
	double		ratio;
	int			yy;
	int			xx;
	t_texture	texture;

	texture = get_texture(data, ray);
	ratio = (double)texture.height / wall_height;
	yy = 0;
	xx = 0;
	yy = (int)floor(y * ratio);
	if (yy >= texture.height)
		yy = texture.height - 1;
	else if (yy < 0)
		yy = 0;
	xx = (int)floor(get_position_texture(data, ray));
	if (xx >= texture.width)
		xx = texture.width - 1;
	else if (xx < 0)
		xx = 0;
	// printf("xx = %d, yy = %d texture width = %d texture height = %d\n", xx, yy, texture.width, texture.height);
	// printf("raytype = %c\n", ray.type);
	return (texture.data[yy * texture.width + xx]);
}
