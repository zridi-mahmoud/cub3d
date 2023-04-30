/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 03:23:32 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/30 14:51:41 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	add_point_to_player(t_var *data, t_point point, t_ray *ray)
{
	t_point	new_point;

	if (ray->angle > 0 && ray->angle < M_PI)
		new_point.y = data->player.y + point.y;
	else
		new_point.y = data->player.y - point.y;
	if (ray->angle > M_PI_2 && ray->angle < 3 * M_PI_2)
		new_point.x = data->player.x - point.x;
	else
		new_point.x = data->player.x + point.x;
	return (new_point);
}

char	get_map_value(t_var *data, t_point point)
{
	int	x;
	int	y;

	x = point.x / (WINDOW_WIDTH / MAP_WIDTH);
	y = point.y / (WINDOW_HEIGHT / MAP_HEIGHT);
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
		return ('1');
	else
		return (data->map[y][x]);
}

t_point	first_h_inter(t_var *data, t_ray *ray)
{
	t_point	point;
	double	tan_alpha;

	tan_alpha = fabs(tan(ray->angle));
	if (ray->angle > 0 && ray->angle < M_PI)
		point.y = (WINDOW_HEIGHT / MAP_HEIGHT)
			- fmod(data->player.y, (WINDOW_HEIGHT / MAP_HEIGHT));
	else
		point.y = fmod(data->player.y, (WINDOW_HEIGHT / MAP_HEIGHT));
	point.x = point.y / tan_alpha;
	return (point);
}

t_point	ith_h_inter(t_var *data, t_ray *ray, int i)
{
	t_point	point;
	double	tan_alpha;
	t_point	first;

	first = first_h_inter(data, ray);
	if (i == 0)
		return (add_point_to_player(data, first, ray));
	tan_alpha = fabs(tan(ray->angle));
	point.y = (float)WINDOW_HEIGHT / MAP_HEIGHT;
	point.x = point.y / tan_alpha;
	point.y = first.y + point.y * i;
	point.x = first.x + point.x * i;
	return (add_point_to_player(data, point, ray));
}

t_point	first_v_inter(t_var *data, t_ray *ray)
{
	t_point	point;
	double	tan_alpha;

	tan_alpha = fabs(tan(ray->angle));
	if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
		point.x = fmod(data->player.x, (WINDOW_WIDTH / MAP_WIDTH));
	else
		point.x = (WINDOW_WIDTH / MAP_WIDTH)
			- fmod(data->player.x, (WINDOW_WIDTH / MAP_WIDTH));
	point.y = point.x * tan_alpha;
	return (point);
}

t_point	ith_v_inter(t_var *data, t_ray *ray, int i)
{
	t_point	point;
	double	tan_alpha;
	t_point	first;

	first = first_v_inter(data, ray);
	if (i == 0)
		return (add_point_to_player(data, first, ray));
	tan_alpha = fabs(tan(ray->angle));
	point.x = (float)(WINDOW_WIDTH / MAP_WIDTH);
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
	while (point.x < WINDOW_WIDTH && point.y < WINDOW_HEIGHT
		&& get_map_value(data, point) != '1')
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
	while (point.x < WINDOW_WIDTH && point.y < WINDOW_HEIGHT
		&& get_map_value(data, point) != '1')
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
		if (ray->angle >= 0 && ray->angle < M_PI)
			ray->type = 'U';
		else
			ray->type = 'D';
		ray->wall = h_point;
		return (dist_h * cos(ray->angle - data->player.angle));
	}
	else
	{
		if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
			ray->type = 'L';
		else
			ray->type = 'R';
		ray->wall = v_point;
		return (dist_v * cos(ray->angle - data->player.angle));
	}
}
