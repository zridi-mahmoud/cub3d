/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:35:04 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/26 15:03:45 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	to_minmap(int x, int y)
{
	float	ratiow;
	float	ratioh;

	ratiow = WINDOW_WIDTH / MINIMAP_WIDTH;
	ratioh = WINDOW_HEIGHT / MINIMAP_HEIGHT;
	if (y == 0)
		return ((int)(x / ratiow));
	else
		return ((int)(x / ratioh + WINDOW_HEIGHT - MINIMAP_HEIGHT));
}

void	put_miniplayer(t_data *data, t_player *player)
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
				my_mlx_pixel_put(data, to_minmap(player->x + x + 3, 0),
					to_minmap(player->y + y + 3, 1), 0x0000FF00);
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
	while (i < MAP_HEIGHT)
	{
		while (j < MAP_WIDTH)
		{
			if (data->map[i][j] == '1')
				put_block_mini(&data->img, j, i, 0x00000000);
			else if (data->map[i][j] == '0')
				put_block_mini(&data->img, j, i, 0x00DDDDDD);
			j++;
		}
		j = 0;
		i++;
	}
}

void	put_block_mini(t_data *data, int x, int y, int color)
{
	int	block_width;
	int	block_height;

	x *= WINDOW_WIDTH / MAP_WIDTH;
	y *= WINDOW_HEIGHT / MAP_HEIGHT;
	block_width = WINDOW_WIDTH / MAP_WIDTH;
	block_height = WINDOW_HEIGHT / MAP_HEIGHT;
	block_width += x;
	block_height += y;
	while (y < block_height - 1)
	{
		while (x < block_width - 1)
		{
			my_mlx_pixel_put(data, to_minmap(x, 0), to_minmap(y, 1), color);
			x++;
		}
		x = x - (WINDOW_WIDTH / MAP_WIDTH) + 1;
		y++;
	}
}
