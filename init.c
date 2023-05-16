/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:50:46 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/16 01:20:20 by mzridi           ###   ########.fr       */
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
		return (0);
	if (open_texture(data, &data->textures.south, data->cub->south_texture))
		return (0);
	if (open_texture(data, &data->textures.west, data->cub->west_texture))
		return (0);
	if (open_texture(data, &data->textures.east, data->cub->east_texture))
		return (0);
	return (1);
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
