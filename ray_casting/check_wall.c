/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:59:03 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/17 00:14:39 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_edge(t_var *data, float dy, float dx)
{
	int	x;
	int	y;
	int	new_x;
	int	new_y;

	x = (int)floor(data->player.x / BLOCK_SIZE);
	y = (int)floor(data->player.y / BLOCK_SIZE);
	new_x = (int)floor((data->player.x + dx) / BLOCK_SIZE);
	new_y = (int)floor((data->player.y + dy) / BLOCK_SIZE);
	if (y >= data->map_height || x >= data->map_widths[y])
		return (1);
	if (new_y >= data->map_height || new_x >= data->map_widths[new_y])
		return (1);
	if (data->map[y][new_x] == '1' && data->map[new_y][x] == '1')
		return (1);
	else
		return (0);
}

int	check(t_var *data, float dy, float dx)
{
	float	x;
	float	y;

	if (check_edge(data, dy, dx))
		return (1);
	x = data->player.x + dx;
	y = data->player.y + dy;
	if (data->map[(int)floor(y) / BLOCK_SIZE]
		[(int)round(x) / BLOCK_SIZE] == '1')
		return (1);
	if (data->map[(int)floor(y + 5) / BLOCK_SIZE]
		[(int)round(x) / BLOCK_SIZE] == '1')
		return (1);
	if (data->map[(int)floor(y) / BLOCK_SIZE]
		[(int)round(x + 5) / BLOCK_SIZE] == '1')
		return (1);
	if (data->map[(int)floor(y - 5) / BLOCK_SIZE]
		[(int)round(x) / BLOCK_SIZE] == '1')
		return (1);
	if (data->map[(int)floor(y) / BLOCK_SIZE]
		[(int)round(x - 5) / BLOCK_SIZE] == '1')
		return (1);
	return (0);
}

int	check_wall(t_var *data, int i, int is_horizontal)
{
	float	dx;
	float	dy;

	if (i == 0)
		return (0);
	dx = cos(normalize_angle(data->player.angle + is_horizontal * M_PI_2))
		* MOVE_SPEED;
	dy = sin(normalize_angle(data->player.angle + is_horizontal * M_PI_2))
		* MOVE_SPEED;
	if (i == 1)
		return (!check(data, dy, dx));
	else
		return (!check(data, -dy, -dx));
}
