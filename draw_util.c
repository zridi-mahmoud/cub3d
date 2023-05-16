/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 01:43:21 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/16 01:45:31 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_block(t_data *data, int x, int y, int color)
{
	int	block_width;
	int	block_height;

	x *= 32;
	y *= 32;
	block_width = 32;
	block_height = 32;
	block_width += x;
	block_height += y;
	y++;
	while (y < block_height - 1)
	{
		while (x < block_width - 1)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		x = x - (32) + 1;
		y++;
	}
}

void	put_point(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 5)
	{
		while (j < 5)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	update_player(t_var *data)
{
	data->player.angle += data->player.rotation_direction * ROTATION_SPEED;
	if (data->player.angle > 2 * M_PI)
		data->player.angle -= 2 * M_PI;
	else if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
	data->player.dx = cos(data->player.angle) * MOVE_SPEED;
	data->player.dy = sin(data->player.angle) * MOVE_SPEED;
	if (check_wall(data, data->player.v_move_direction, 0))
	{
		data->player.x += data->player.v_move_direction * data->player.dx;
		data->player.y += data->player.v_move_direction * data->player.dy;
	}
	data->player.dx = cos(data->player.angle + M_PI / 2) * MOVE_SPEED;
	data->player.dy = sin(data->player.angle + M_PI / 2) * MOVE_SPEED;
	if (check_wall(data, data->player.h_move_direction, 1))
	{
		data->player.x += data->player.h_move_direction * data->player.dx;
		data->player.y += data->player.h_move_direction * data->player.dy;
	}
}

int	render_next_frame(t_var *data)
{
	update_player(data);
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	draw_3d(data);
	draw_minimap(data);
	put_miniplayer(data, &data->player);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	return (0);
}
