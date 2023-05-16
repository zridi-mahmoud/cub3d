/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 01:20:01 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/17 00:14:39 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_map(t_var *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	data->map_height = map_height(map);
	data->map_widths = (int *)malloc(sizeof(int) * data->map_height);
	if (!data->map_widths)
		return (0);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'W' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'N')
			{
				init_player(&data->player, j, i, map[i][j]);
				map[i][j] = '0';
			}
			j++;
		}
		data->map_widths[i] = j;
		i++;
	}
	return (1);
}

t_var	*init_data(t_cub3D *cub)
{
	t_var	*data;
	char	**map;

	data = malloc(sizeof(t_var));
	if (!data)
		return (NULL);
	map = &cub->map_arr[cub->first_line];
	if (!init_map(data, map))
		return (free(data), NULL);
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
		return (free(data->map_widths), free(data), NULL);
	return (data);
}
