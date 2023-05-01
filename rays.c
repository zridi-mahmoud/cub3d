/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:36:39 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/01 19:55:22 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_facing_up(float angle)
{
	if (angle > M_PI)
		return (1);
	return (0);
}

int	is_facing_left(float angle)
{
	if (angle > M_PI_2 && angle < 3 * M_PI_2)
		return (1);
	return (0);
}

void	draw_ray(t_var *data, t_ray *ray)
{
	float	x;
	float	y;
	int		i;

	x = ray->x;
	y = ray->y;
	i = 0;
	while (i++ < 50)
	{
		x += ray->dx;
		y += ray->dy;
		my_mlx_pixel_put(&data->img, to_minmap(x, 0),
			to_minmap(y, 1), 0x00FF0000);
	}
}

void	draw_rays(t_var *data)
{
	int		i;
	t_ray	ray;

	i = 0;
	while (data->player.angle - 0.03 + 0.01 * i
		< data->player.angle + 0.03)
	{
		ray.x = data->player.x + 4;
		ray.y = data->player.y + 4;
		ray.angle = data->player.angle - 0.03 + 0.01 * i;
		ray.dx = cos(ray.angle);
		ray.dy = sin(ray.angle);
		draw_ray(data, &ray);
		i++;
	}
}
