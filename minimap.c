/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:35:04 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/16 01:05:30 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	to_minmap(t_var *data, int x, int y)
{
	float	ratiow;
	float	ratioh;

	(void)data;
	ratiow = 5;
	ratioh = 5;
	if (y == 0)
		return ((int)(x / ratiow));
	else
		return ((int)(x / ratioh));
}

void	put_miniplayer(t_var *data, t_player *player)
{
	int	x;
	int	y;
	int	offset;

	offset = 3;
	x = -3;
	y = -3;
	while (y < offset)
	{
		while (x < offset)
		{
			if (x * x + y * y <= offset * offset)
				my_mlx_pixel_put(&data->img,
					to_minmap(data, player->x + x + 3, 0),
					to_minmap(data, player->y + y + 3, 1), 0x000000FF);
			x++;
		}
		x = -3;
		y++;
	}
}

void	draw_minimap(t_var *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->map_height)
	{
		while (j < data->map_widths[i])
		{
			if (data->map[i][j] == '1')
				put_block_mini(data, j, i, 0x00DD0000);
			j++;
		}
		j = 0;
		i++;
	}
}

void	put_block_mini(t_var *data, int x, int y, int color)
{
	int	block_width;
	int	block_height;

	x *= BLOCK_SIZE;
	y *= BLOCK_SIZE;
	block_width = BLOCK_SIZE;
	block_height = BLOCK_SIZE;
	block_width += x;
	block_height += y;
	while (y < block_height - 1)
	{
		while (x < block_width - 1)
		{
			my_mlx_pixel_put(&data->img, to_minmap(data, x, 0),
				to_minmap(data, y, 1), color);
			x++;
		}
		x = x - BLOCK_SIZE + 1;
		y++;
	}
}
