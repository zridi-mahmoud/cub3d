/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 02:54:54 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/03 22:15:04 by mzridi           ###   ########.fr       */
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

	offset = 4;
	x = -4;
	y = -4;
	while (y < offset)
	{
		while (x < offset)
		{
			if (x * x + y * y <= offset * offset)
				my_mlx_pixel_put(data, player->x + x + 4,
					player->y + y + 4, 0x0000FF00);
			x++;
		}
		x = -4;
		y++;
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
	y++;
	while (y < block_height - 1)
	{
		while (x < block_width - 1)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		x = x - (window_width / map_width) + 1;
		y++;
	}
}

void	put_direction(t_data *data, t_player *player)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = player->x + 4;
	y = player->y + 4;
	while (i < 5)
	{
		x -= player->dx;
		y -= player->dy;
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
		my_mlx_pixel_put(data, x + 0.5, y, 0x00FF0000);
		my_mlx_pixel_put(data, x, y + 0.5, 0x00FF0000);
		my_mlx_pixel_put(data, x - 0.5, y, 0x00FF0000);
		my_mlx_pixel_put(data, x, y - 0.5, 0x00FF0000);
		i++;
	}
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
}

void	render_next_frame(t_var *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, window_width, window_height);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	draw_map(data);
	put_player(&data->img, &data->player);
	put_direction(&data->img, &data->player);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

void	init_player(t_player *player, int i, int j)
{
	player->x = j * window_width / map_width + 1;
	player->y = i * window_height / map_height + 1;
	player->angle = 0;
	player->dx = 0;
	player->dy = 0;
	if (map[i][j] == 'W')
	{
		player->angle = 3 * M_PI / 2;
		player->dx = -1;
	}
	else if (map[i][j] == 'S')
	{
		player->angle = M_PI;
		player->dy = 1;
	}
	else if (map[i][j] == 'E')
	{
		player->angle = M_PI / 2;
		player->dx = 1;
	}
	else if (map[i][j] == 'N')
	{
		player->angle = 0;
		player->dy = -1;
	}
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
			if (map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E'
					|| map[i][j] == 'N')
				init_player(&data->player, j, i);
			j++;
		}
		j = 0;
		i++;
	}
	return (data);
}

int	key_press(int keycode, t_var *data)
{
	if (keycode == 0 || keycode == 123)
	{
		data->player.angle -= 0.15;
		if (data->player.angle < 0)
			data->player.angle += 2 * M_PI;
	}
	else if (keycode == 2 || keycode == 124)
	{
		data->player.angle += 0.15;
		if (data->player.angle > 2 * M_PI)
			data->player.angle += 2 * M_PI;
	}
	else if (keycode == 13 || keycode == 126)
	{
		data->player.y -= data->player.dy;
		data->player.x -= data->player.dx;
	}
	else if (keycode == 1 || keycode == 125)
	{
		data->player.y += data->player.dy;
		data->player.x += data->player.dx;
	}
	else if (keycode == 53)
		exit(0);
	else
		return (0);
	data->player.dx = cos(data->player.angle) * 10;
	data->player.dy = sin(data->player.angle) * 10;
	render_next_frame(data);
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
