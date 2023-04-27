/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:49:15 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/27 10:16:23 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color (int type)
{
	if (type == 'D')
		return (WALL_COLOR_D);
	else if (type == 'U')
		return (WALL_COLOR_U);
	else if (type == 'L')
		return (WALL_COLOR_L);
	else if (type == 'R')
		return (WALL_COLOR_R);
	else
		return (0);
}

void	draw_wall(t_var *data, int x, t_ray *ray)
{
	int		y;
	double	wall_height;
	double	wall_top;
	double	wall_bottom;

	y = 0;
	wall_height = (MAP_HEIGHT * (WINDOW_WIDTH / tan(FOV / 2)))
		/ distance_wall(data, ray);
	wall_top = WINDOW_HEIGHT / 2 - wall_height / 2;
	wall_bottom = WINDOW_HEIGHT / 2 + wall_height / 2;
	while (y < WINDOW_HEIGHT)
	{
		if (y < wall_top)
			my_mlx_pixel_put(&data->img, x, y, SKY_COLOR);
		else if (y >= wall_top && y <= wall_bottom)
		{
			my_mlx_pixel_put(&data->img, x, y, get_color(ray->type));
		}
		else
			my_mlx_pixel_put(&data->img, x, y, GROUND_COLOR);
		y++;
	}
}

double normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void draw_3d(t_var *data)
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
