/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:50:46 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/28 19:33:05 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player, int i, int j, char dir)
{
	player->x = j * WINDOW_WIDTH / MAP_WIDTH + 1;
	player->y = i * WINDOW_HEIGHT / MAP_HEIGHT + 1;
	player->angle = 0;
	player->dx = 0;
	player->dy = 0;
	if (dir == 'W')
	{
		player->angle = M_PI;
		player->dx = -1;
	}
	else if (dir == 'S')
	{
		player->angle = M_PI / 2;
		player->dy = 1;
	}
	else if (dir == 'E')
	{
		player->angle = 0;
		player->dx = 1;
	}
	else if (dir == 'N')
	{
		player->angle = 3 * M_PI / 2;
		player->dy = -1;
	}
}

t_var	*init_data(char **map)
{
	t_var	*data;
	int		i;
	int		j;

	i = -1;
	data = malloc(sizeof(t_var));
	while (i < MAP_HEIGHT - 1)
	{
		j = 0 * i++;
		while (j < MAP_WIDTH)
		{
			if (map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E'
					|| map[i][j] == 'N')
			{
				map[i][j] = '0';
				init_player(&data->player, j, i, map[i][j]);
			}
			j++;
		}
	}
	data->map = map;
	data->mlx = mlx_init();
	data->player.rotation_direction = 0;
	data->player.v_move_direction = 0;
	data->player.h_move_direction = 0;
	data->player.mouse_x = 0;
	data->mlx_win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"CALL OF DUTY MODERN WARFARE 23 BETA");
	data->img.img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	return (data);
}
