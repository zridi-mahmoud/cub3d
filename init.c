/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:50:46 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/02 23:28:36 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player, int i, int j, char dir)
{
	player->x = i * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->y = j * BLOCK_SIZE + BLOCK_SIZE / 2;
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

int	open_texture(t_var *data, t_texture *t, char *path)
{
	t->img = mlx_xpm_file_to_image(data->mlx, path,
			&t->width, &t->height);
	if (!t->img)
		return (printf("Error\n while opening texture %s\n", path), 1);
	t->data = (int *)mlx_get_data_addr(t->img,
			&t->bpp, &t->size_line,
			&t->endian);
	return (0);
}

int	init_textures(t_var *data)
{
	if (open_texture(data, &data->textures.north, data->cub->north_texture))
		return (1);
	printf("north texture opened\n");
	if (open_texture(data, &data->textures.south, data->cub->south_texture))
		return (1);
	printf("south texture opened\n");
	if (open_texture(data, &data->textures.west, data->cub->west_texture))
		return (1);
	printf("west texture opened\n");
	if (open_texture(data, &data->textures.east, data->cub->east_texture))
		return (1);
	printf("east texture opened\n");
	return (0);
}

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	map_width(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

t_var	*init_data(t_cub3D *cub)
{
	t_var	*data;
	int		i;
	int		j;
	char	**map;

	i = 0;
	data = malloc(sizeof(t_var));
	map = &cub->map_arr[cub->first_line];
	if (!data)
		return (NULL);
	data->map_height = map_height(map);
	data->map_widths = (int *)malloc(sizeof(int) * data->map_height);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E'
					|| map[i][j] == 'N')
			{
				init_player(&data->player, j, i, map[i][j]);
				map[i][j] = '0';
			}
			j++;
		}
		data->map_widths[i] = j;
		if (j > data->map_width)
			data->map_width = j;
		i++;
	}
	data->map_height = i;
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
	data->cub = cub;
	if (!init_textures(data))
		return (NULL);
	return (data);
}
