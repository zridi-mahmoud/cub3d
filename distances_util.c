/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 01:36:09 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/16 01:36:16 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	ith_v_inter(t_var *data, t_ray *ray, int i)
{
	t_point	point;
	double	tan_alpha;
	t_point	first;

	first = first_v_inter(data, ray);
	if (i == 0)
		return (add_point_to_player(data, first, ray));
	tan_alpha = fabs(tan(ray->angle));
	point.x = (float)BLOCK_SIZE;
	point.y = point.x * tan_alpha;
	point.x = first.x + point.x * i;
	point.y = first.y + point.y * i;
	return (add_point_to_player(data, point, ray));
}

t_point	dist_to_h_wall(t_var *data, t_ray *ray)
{
	t_point	point;
	int		i;

	i = 0;
	point = ith_h_inter(data, ray, i++);
	if (is_facing_up(ray->angle))
		point.y--;
	while (get_map_value(data, point) != '1')
	{
		point = ith_h_inter(data, ray, i);
		if (is_facing_up(ray->angle))
			point.y--;
		i++;
	}
	if (is_facing_up(ray->angle))
		point.y++;
	return (point);
}

t_point	dist_to_v_wall(t_var *data, t_ray *ray)
{
	t_point	point;
	int		i;

	i = 0;
	point = ith_v_inter(data, ray, i++);
	if (is_facing_left(ray->angle))
		point.x--;
	while (get_map_value(data, point) != '1')
	{
		point = ith_v_inter(data, ray, i);
		if (is_facing_left(ray->angle))
			point.x--;
		i++;
	}
	if (is_facing_left(ray->angle))
		point.x++;
	return (point);
}

double	distance(t_var *data, t_point point, t_ray *ray)
{
	double	x;
	double	y;

	(void)ray;
	x = data->player.x - point.x;
	y = data->player.y - point.y;
	return (sqrt(x * x + y * y));
}

double	distance_wall(t_var *data, t_ray *ray)
{
	t_point	h_point;
	t_point	v_point;
	double	dist_h;
	double	dist_v;

	h_point = dist_to_h_wall(data, ray);
	v_point = dist_to_v_wall(data, ray);
	dist_h = distance(data, h_point, ray);
	dist_v = distance(data, v_point, ray);
	if (dist_h <= dist_v)
	{
		ray->type = 'D';
		if (ray->angle >= 0 && ray->angle < M_PI)
			ray->type = 'U';
		ray->wall = h_point;
		return (dist_h * cos(ray->angle - data->player.angle));
	}
	else
	{
		ray->type = 'R';
		if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
			ray->type = 'L';
		ray->wall = v_point;
		return (dist_v * cos(ray->angle - data->player.angle));
	}
}
