/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:40:07 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/25 19:22:50 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(t_var *data, int i)
{
	if (i == 1)
	{
		if (data->map[(int)(data->player.y + data->player.dy) / (WINDOW_HEIGHT / MAP_HEIGHT)]
			[(int)(data->player.x + data->player.dx) / (WINDOW_WIDTH / MAP_WIDTH)] == '1')
			return (0);
	}
	else
	{
		if (data->map[(int)(data->player.y - data->player.dy) / (WINDOW_HEIGHT / MAP_HEIGHT)]
			[(int)(data->player.x - data->player.dx) / (WINDOW_WIDTH / MAP_WIDTH)] == '1')
			return (0);
	}
	return (1);
}

int	key_press(int keycode, t_var *data)
{
	if (keycode == 0 || keycode == 123)
	{
		data->player.angle -= 0.15;
		if (data->player.angle < 0)
			data->player.angle += 2 * M_PI;
	}
	else if (keycode == 2 || keycode == 124)
	{
		data->player.angle += 0.15;
		if (data->player.angle > 2 * M_PI)
			data->player.angle -= 2 * M_PI;
	}
	else if ((keycode == 13 || keycode == 126) && check_wall(data, 1))
	{
		data->player.y += data->player.dy;
		data->player.x += data->player.dx;
	}
	else if ((keycode == 1 || keycode == 125) && check_wall(data, 0))
	{
		data->player.y -= data->player.dy;
		data->player.x -= data->player.dx;
	}
	else if (keycode == 53)
		exit(0);
	else
		return (0);
	data->player.dx = cos(data->player.angle) * 10;
	data->player.dy = sin(data->player.angle) * 10;
	render_next_frame(data);
	return (0);
}
