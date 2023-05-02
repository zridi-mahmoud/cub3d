/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:50:46 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/02 00:59:19 by mzridi           ###   ########.fr       */
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
// t_textures {north, south, east, west, sprite};

int	init_textures(t_var *data)
{
	data->textures.north.img = mlx_xpm_file_to_image(data->mlx, "./textures/test1337.xpm",
			&data->textures.north.width, &data->textures.north.height);
	if (!data->textures.north.img)
		return (printf("Error\nInvalid path for north texture"), 1);
	data->textures.north.data = (int *)mlx_get_data_addr(data->textures.north.img,
			&data->textures.north.bpp, &data->textures.north.size_line,
			&data->textures.north.endian);
	data->textures.south.img = data->textures.north.img;
	data->textures.south.data = data->textures.north.data;
	data->textures.south.width = data->textures.north.width;
	data->textures.south.height = data->textures.north.height;
	data->textures.south.bpp = data->textures.north.bpp;
	data->textures.south.size_line = data->textures.north.size_line;
	data->textures.south.endian = data->textures.north.endian;
	data->textures.east.img = data->textures.north.img;
	data->textures.east.data = data->textures.north.data;
	data->textures.east.width = data->textures.north.width;
	data->textures.east.height = data->textures.north.height;
	data->textures.east.bpp = data->textures.north.bpp;
	data->textures.east.size_line = data->textures.north.size_line;
	data->textures.east.endian = data->textures.north.endian;
	data->textures.west.img = data->textures.north.img;
	data->textures.west.data = data->textures.north.data;
	data->textures.west.width = data->textures.north.width;
	data->textures.west.height = data->textures.north.height;
	data->textures.west.bpp = data->textures.north.bpp;
	data->textures.west.size_line = data->textures.north.size_line;
	data->textures.west.endian = data->textures.north.endian;
	
	// data->textures.south.img = mlx_xpm_file_to_image(data->mlx, paths[1],
	// 		&data->textures.south.width, &data->textures.south.height);
	// if (!data->textures.south.img)
	// 	return (printf("Error\nInvalid path for south texture\n"), 1);
	// data->textures.south.data = (int *)mlx_get_data_addr(data->textures.south.img,
	// 		&data->textures.south.bpp, &data->textures.south.size_line,
	// 		&data->textures.south.endian);
	// data->textures.east.img = mlx_xpm_file_to_image(data->mlx, paths[2],
	// 		&data->textures.east.width, &data->textures.east.height);
	// if (!data->textures.east.img)
	// 	return (printf("Error\nInvalid path for east texture\n"), 1);
	// data->textures.east.data = (int *)mlx_get_data_addr(data->textures.east.img,
	// 		&data->textures.east.bpp, &data->textures.east.size_line,
	// 		&data->textures.east.endian);
	// data->textures.west.img = mlx_xpm_file_to_image(data->mlx, paths[3],
	// 		&data->textures.west.width, &data->textures.west.height);
	// if (!data->textures.west.img)
	// 	return (printf("Error\nInvalid path for west texture\n"), 1);
	// data->textures.west.data = (int *)mlx_get_data_addr(data->textures.west.img,
	// 		&data->textures.west.bpp, &data->textures.west.size_line,
	// 		&data->textures.west.endian);
	// if (!data->textures.north.data || !data->textures.south.data
	// 	|| !data->textures.east.data || !data->textures.west.data)
	// 	return (printf("Error\nInvalid path for texture\n"), 1);
	return (1);
}

t_var	*init_data(t_cub3D *cub)
{
	t_var	*data;
	int		i;
	int		j;
	char	**map;

	i = -1;
	data = malloc(sizeof(t_var));
	map = &cub->map_arr[cub->first_line];
	if (!data)
		return (NULL);
	// printf("map height: %d max width: %d\n",cub->map_height, cub->map_width);
	while (map[++i])
	{
		j = 0;
		// printf("|%s|\n", map[i]);
		while (map[i][j])
		{
			if (map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E'
					|| map[i][j] == 'N')
			{
				map[i][j] = '0';
				init_player(&data->player, j, i, map[i][j]);
				printf("player x: %f y: %f\n", data->player.x, data->player.y);
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
	if (!init_textures(data))
		return (NULL);
	return (data);
}
