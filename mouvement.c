/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:40:07 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/27 18:17:28 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_wall(t_var *data, int i)
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

void	move_player_h(t_var *data, int i)
{
	t_point	p;

	if (i == 1)
	{
		p.x = data->player.x + cos(data->player.angle + M_PI_2) * 10;
		p.y = data->player.y + sin(data->player.angle + M_PI_2) * 10;
	}
	else
	{
		p.x = data->player.x - cos(data->player.angle + M_PI_2) * 10;
		p.y = data->player.y - sin(data->player.angle + M_PI_2) * 10;
	}
	if (get_map_value(data, p) != '1')
	{
		data->player.y += sin(data->player.angle + M_PI_2) * 10;
		data->player.x += cos(data->player.angle + M_PI_2) * 10;
	}
}

int	key_press(int keycode, t_var *data)
{
	if (keycode == 0 || keycode == 123)
		data->player.rotation_direction = -1;
	else if (keycode == 2 || keycode == 124)
		data->player.rotation_direction = 1;
	else if ((keycode == 13 || keycode == 126) && check_wall(data, 1))
		data->player.move_direction = 1;
	else if ((keycode == 1 || keycode == 125) && check_wall(data, 0))
		data->player.move_direction = -1;
	else if (keycode == 53)
		exit(0);
	else
		return (0);
	render_next_frame(data);
	return (0);
}

int	key_release(int keycode, t_var *data)
{
	if (keycode == 0 || keycode == 123 || keycode == 2 || keycode == 124)
		data->player.rotation_direction = 0;
	else if (keycode == 13 || keycode == 126 || keycode == 1 || keycode == 125)
		data->player.move_direction = 0;
	else
		return (0);
	return (0);
}
