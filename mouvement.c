/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:40:07 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/30 13:52:53 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(t_var *data, int i)
{
	float	dx;
	float	dy;

	dx = cos(data->player.angle) * MOVE_SPEED;
	dy = sin(data->player.angle) * MOVE_SPEED;
	if (i == 1)
	{
		if (data->map[(int)round(data->player.y + dy - is_facing_up(data->player.angle)) / (WINDOW_HEIGHT
					/ MAP_HEIGHT)]
			[(int)round(data->player.x + dx - is_facing_left(data->player.angle)) / (WINDOW_WIDTH / MAP_WIDTH)
				] == '1')
			return (0);
	}
	else
	{
		if (data->map[(int)round(data->player.y - dy - !is_facing_up(data->player.angle))
				/ (WINDOW_HEIGHT / MAP_HEIGHT)]
			[(int)round(data->player.x - dx - !is_facing_left(data->player.angle))
				/ (WINDOW_WIDTH / MAP_WIDTH)] == '1')
			return (0);
	}
	return (1);
}

void	move_player_h(t_var *data, int i)
{
	t_point	p;

	if (i == 1)
	{
		p.x = data->player.x + cos(data->player.angle + M_PI_2) * MOVE_SPEED;
		p.y = data->player.y + sin(data->player.angle + M_PI_2) * MOVE_SPEED;
		if (!is_facing_up(data->player.angle))
			p.x -= 1;
		if (is_facing_left(data->player.angle))
			p.y -= 1;
	}
	else
	{
		p.x = data->player.x - cos(data->player.angle + M_PI_2) * MOVE_SPEED;
		p.y = data->player.y - sin(data->player.angle + M_PI_2) * MOVE_SPEED;
		if (is_facing_up(data->player.angle))
			p.x -= 1;
		if (!is_facing_left(data->player.angle))
			p.y -= 2;
	}
	if (get_map_value(data, p) != '1')
	{
		data->player.y += sin(data->player.angle + M_PI_2) * MOVE_SPEED;
		data->player.x += cos(data->player.angle + M_PI_2) * MOVE_SPEED;
	}
}

int	key_press(int keycode, t_var *data)
{
	if (keycode == 0)
		data->player.rotation_direction = -1;
	else if (keycode == 2)
		data->player.rotation_direction = 1;
	else if ((keycode == 13 || keycode == 126) && check_wall(data, 1))
		data->player.v_move_direction = 1;
	else if ((keycode == 1 || keycode == 125) && check_wall(data, 0))
		data->player.v_move_direction = -1;
	else if (keycode == 124)
		data->player.h_move_direction = 1;
	else if (keycode == 123)
		data->player.h_move_direction = -1;
	else if (keycode == 53)
		exit(0);
	else
		return (0);
	render_next_frame(data);
	return (0);
}

int	key_release(int keycode, t_var *data)
{
	if (keycode == 0 || keycode == 2)
		data->player.rotation_direction = 0;
	else if (keycode == 13 || keycode == 1 || keycode == 126 || keycode == 125)
		data->player.v_move_direction = 0;
	else if (keycode == 123 || keycode == 124)
		data->player.h_move_direction = 0;
	else
		return (0);
	return (0);
}

int	mouse_move(int x, int y, t_var *data)
{
	mlx_mouse_hide(data->mlx_win);
	mlx_mouse_get_pos(data->mlx_win, &x, &y);
	mlx_mouse_move(data->mlx_win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	(void)y;
	if (x < WINDOW_WIDTH * 0.49)
		data->player.rotation_direction = -1;
	else if (x > 0.51 * (WINDOW_WIDTH))
		data->player.rotation_direction = 1;
	else
		data->player.rotation_direction = 0;
	data->player.mouse_x = x;
	return (0);
}
