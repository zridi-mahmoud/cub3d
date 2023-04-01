/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 02:54:54 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/01 03:08:12 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_player(t_data *data, t_player *player)
{
	int	x;
	int	y;
	int	offset;

	offset = 8;
	x = 0;
	y = 0;
	printf("player x: %f, player y: %f \n", player->x, player->y);
	while (x < offset)
	{
		while (y < offset)
		{
			my_mlx_pixel_put(data, player->x + x, player->y + y, 0x0000FF00);
			y++;
		}
		y = 0;
		x++;
	}
}

void	put_block(t_data *data, int x, int y, int color)
{
	int	block_width;
	int	block_height;

	x *= window_width / map_width;
	y *= window_height / map_height;
	block_width = window_width / map_width;
	block_height = window_height / map_height;
	block_width += x;
	block_height += y;
	while (y < block_height)
	{
		while (x < block_width)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		x = x - (window_width / map_width);
		y++;
	}
}

void	render_next_frame(t_var *data)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

void	draw_map(t_var *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map_height)
	{
		while (j < map_width)
		{
			if (map[i][j] == '1')
				put_block(&data->img, j, i, 0x00000000);
			else
				put_block(&data->img, j, i, 0x00FFFFFF);
			j++;
		}
		j = 0;
		i++;
	}
	put_player(&data->img, &data->player);
	render_next_frame(data);
}

t_var	*init_data()
{
	t_var	*data;
	int		i;
	int		j;

	i = 0;
	j = 0;
	data = malloc(sizeof(t_var));
	while (i < map_height)
	{
		while (j < map_width)
		{
			if (map[i][j] == 'W')
			{
				data->player.x = j * window_width / map_width + 1;
				data->player.y = i * window_height / map_height + 1;
				data->player.dx = 0;
				data->player.dy = 0;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (data);
}

int	key_press(int keycode, t_var *data)
{
	printf("keycode: %d \n", keycode);
	if (keycode == 0 || keycode == 123)
		data->player.x -= 5;
	else if (keycode == 2 || keycode == 124)
		data->player.x += 5;
	else if (keycode == 13 || keycode == 126)
		data->player.y -= 5;
	else if (keycode == 1 || keycode == 125)
		data->player.y += 5;
	else if (keycode == 53)
		exit(0);
	else
		return (0);
	printf("player x: %f, player y: %f \n", data->player.x, data->player.y);
	draw_map(data);
	return (0);
}

int	main(void)
{
	t_var	*data;

	data = init_data();
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, window_width, window_height,
			"CALL OF DUTY MODERN WARFARE 23");
	data->img.img = mlx_new_image(data->mlx, window_width, window_height);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	draw_map(data);
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_press, data);
	mlx_loop(data->mlx);
}
