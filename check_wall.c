/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:59:03 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/01 23:53:19 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_error_marg(t_var *data, int i)
{
	if (i == 1)
	{
		if (is_facing_up(data->player.angle) || is_facing_left(data->player.angle))
			return (data->player.v_move_direction * -5);
		else
			return (data->player.v_move_direction * 5);
	}
	else if (i == 3 || i == 4)
	{
		if (is_facing_up(data->player.angle - M_PI_2) || is_facing_left(data->player.angle - M_PI_2))
			return (data->player.h_move_direction * -5);
		else
			return (data->player.h_move_direction * 5);
	}
	return (0);
}

int	check_wall(t_var *data, int i)
{
	float	dx;
	float	dy;

	dx = cos(data->player.angle) * MOVE_SPEED;
	dy = sin(data->player.angle) * MOVE_SPEED;
	if (i == 1)
	{
		if (data->map[(int)round(data->player.y + dy
					+ get_error_marg(data, 1))
				/ (WINDOW_HEIGHT / MAP_HEIGHT)]
			[(int)round(data->player.x + dx + get_error_marg(data, 1)
				) / (WINDOW_WIDTH / MAP_WIDTH)] == '1')
			return (0);
	}
	else
	{
		if (data->map[(int)round(data->player.y - dy
					+ get_error_marg(data, 1))
				/ (WINDOW_HEIGHT / MAP_HEIGHT)]
			[(int)round(data->player.x
					- dx + get_error_marg(data, 1)
					) / (WINDOW_WIDTH / MAP_WIDTH)] == '1')
			return (0);
	}
	return (1);
}

int	check_wall_h(t_var *data, int i)
{
	float	dx;
	float	dy;

	dx = cos(data->player.angle + M_PI_2) * MOVE_SPEED;
	dy = sin(data->player.angle + M_PI_2) * MOVE_SPEED;
	if (i == 1)
	{
		if (data->map[(int)round(data->player.y + dy
					+ get_error_marg(data, 2))
				/ (WINDOW_HEIGHT / MAP_HEIGHT)]
			[(int)round(data->player.x + dx + get_error_marg(data, 2)
				) / (WINDOW_WIDTH / MAP_WIDTH)] == '1')
			return (0);
	}
	else
	{
		if (data->map[(int)round(data->player.y - dy
					+ get_error_marg(data, 2))
				/ (WINDOW_HEIGHT / MAP_HEIGHT)]
			[(int)round(data->player.x
					- dx + get_error_marg(data, 2)
					) / (WINDOW_WIDTH / MAP_WIDTH)] == '1')
			return (0);
	}
	return (1);
}
