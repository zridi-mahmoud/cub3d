/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 02:54:54 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/26 12:12:20 by mzridi           ###   ########.fr       */
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

	x *= WINDOW_WIDTH / MAP_WIDTH;
	y *= WINDOW_HEIGHT / MAP_HEIGHT;
	block_width = WINDOW_WIDTH / MAP_WIDTH;
	block_height = WINDOW_HEIGHT / MAP_HEIGHT;
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
		x = x - (WINDOW_WIDTH / MAP_WIDTH) + 1;
		y++;
	}
}
// draw the intersection of the ray with the wall in the minimap

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

// void	draaa(t_var *data)
// {
// 	t_ray	ray;
// 	t_point	inter_h;
// 	t_point	inter_v;
// 	int		i;

// 	i = 0;
// 	ray.angle = data->player.angle;
// 	ray.x = data->player.x;
// 	ray.y = data->player.y;
// 	while (i < 2)
// 	{
// 		inter_h = ith_h_inter(data, &ray, i);
// 		put_point(&data->img, to_minmap(inter_h.x, 0), to_minmap(inter_h.y, 1), 0x0000FF);
// 		inter_v = ith_v_inter(data, &ray, i);
// 		put_point(&data->img, to_minmap(inter_v.x, 0), to_minmap(inter_v.y, 1), 0x00FFFF00);
// 		i++;
// 	}
// }


void	render_next_frame(t_var *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	draw_3d(data);
	draw_minimap(data);
	put_miniplayer(&data->img, &data->player);
	draw_rays(data);
	// draaa(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

int	main(void)
{
	t_var	*data;
	int		j;
	int		i;
	char	*tmp_map[11] = {
		"111111111111111",
		"1000E0000000001",
		"100010111011101",
		"101010111011101",
		"100010111011101",
		"101110111011101",
		"101110111011101",
		"100000000000001",
		"100000000000001",
		"111111111111111"
	};
	char	**map;

	i = 0;
	map = (char **)malloc(sizeof(char *) * 11);
	if (!map)
		return (0);
	while (tmp_map[i])
	{
		map[i] = (char *)malloc(sizeof(char) * 16);
		if (!map[i])
			return (0);
		j = 0;
		while (tmp_map[i][j])
		{
			map[i][j] = tmp_map[i][j];
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
	data = init_data(map);
	render_next_frame(data);
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_press, data);
	mlx_loop(data->mlx);
}
