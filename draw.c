/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:49:15 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/16 01:05:02 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_color(t_var *data, t_ray *ray, int y,
		t_point texture_column)
{
	t_texture	texture;
	int			t_x;
	int			t_y;

	t_x = (int)texture_column.x;
	t_y = (int)(texture_column.y * y);
	if (t_x >= texture.width)
		t_x = texture.width - 1;
	if (t_y >= texture.height)
		t_y = texture.height - 1;
	if (t_x < 0)
		t_x = 0;
	if (t_y < 0)
		t_y = 0;
	texture = get_texture(data, *ray);
	return (texture.data[t_y * texture.width + t_x]);
}

unsigned int	get_color_0x(t_var *data, char type)
{
	if (type == 'c')
		return (data->cub->ceiling_color_int[0] << 16
			| data->cub->ceiling_color_int[1] << 8
			| data->cub->ceiling_color_int[2]);
	else
		return (data->cub->floor_color_int[0] << 16
			| data->cub->floor_color_int[1] << 8
			| data->cub->floor_color_int[2]);
}

void	draw_wall(t_var *data, int x, t_ray *ray)
{
	int		y;
	double	wall_height;
	double	wall_top;
	double	wall_bottom;
	t_point	texture_column;

	y = 0;
	wall_height = (MAP_HEIGHT * (WINDOW_WIDTH / tan(FOV / 2)))
		/ distance_wall(data, ray);
	wall_top = WINDOW_HEIGHT / 2 - wall_height / 2;
	wall_bottom = WINDOW_HEIGHT / 2 + wall_height / 2;
	texture_column = get_texture_column(data, *ray, y - wall_top, wall_height);
	while (y < WINDOW_HEIGHT)
	{
		if (y < wall_top)
			my_mlx_pixel_put(&data->img, x, y, get_color_0x(data, 'c'));
		else if (y > wall_top && y < wall_bottom)
		{
			my_mlx_pixel_put(&data->img, x, y,
				get_color(data, ray, y - wall_top, texture_column));
		}
		else
			my_mlx_pixel_put(&data->img, x, y, get_color_0x(data, 'f'));
		y++;
	}
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void	draw_3d(t_var *data)
{
	int		i;
	t_ray	ray;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		ray.angle = data->player.angle - FOV / 2 + FOV * i / WINDOW_WIDTH;
		ray.angle = normalize_angle(ray.angle);
		ray.dx = cos(ray.angle);
		ray.dy = sin(ray.angle);
		ray.x = data->player.x;
		ray.y = data->player.y;
		draw_wall(data, i, &ray);
		i++;
	}
}
