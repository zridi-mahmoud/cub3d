/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 02:54:54 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/30 15:08:43 by mzridi           ###   ########.fr       */
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

void	update_player(t_var *data)
{
	data->player.angle += data->player.rotation_direction * ROTATION_SPEED;
	if (data->player.angle > 2 * M_PI)
		data->player.angle -= 2 * M_PI;
	else if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
	data->player.dx = cos(data->player.angle) * MOVE_SPEED;
	data->player.dy = sin(data->player.angle) * MOVE_SPEED;
	if (check_wall(data, data->player.v_move_direction))
	{
		data->player.x += data->player.v_move_direction * data->player.dx;
		data->player.y += data->player.v_move_direction * data->player.dy;
	}
	data->player.dx = cos(data->player.angle + M_PI / 2) * MOVE_SPEED;
	data->player.dy = sin(data->player.angle + M_PI / 2) * MOVE_SPEED;
	if (check_wall(data, data->player.h_move_direction))
	{
		data->player.x += data->player.h_move_direction * data->player.dx;
		data->player.y += data->player.h_move_direction * data->player.dy;
	}
}

int	render_next_frame(t_var *data)
{
	update_player(data);
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	draw_3d(data);
	draw_minimap(data);
	put_miniplayer(&data->img, &data->player);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	return (0);
}

	// char	*relative_path = "./test.xpm";
	// int		img_width;
	// int		img_height;

	// mlx = mlx_init();
	// img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);

int	main(void)
{
	t_var	*data;
	int		j;
	int		i;
	char	*tmp_map[11] = {
		"11111111111",
		"1000E000001111",
		"10001011101101",
		"10101011101101",
		"10001011100001",
		"10110011101101",
		"10111011101111",
		"100000000001",
		"100000000001",
		"111111111111"
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
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, &key_release, data);
	mlx_hook(data->mlx_win, 6, 1L << 6, &mouse_move, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
	return (0);
}

// int main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	void	*img;
// 	int		img_width;
// 	int		img_height;
// 	int		bpp;
// 	char	*relative_path = "./images/test1337.xpm";
// 	int		size_line;
// 	int		endian;

// 	mlx = mlx_init();

// 	mlx_win = mlx_new_window(mlx, 225, 225, "Hello world!");
// 	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
// 	int *my_image_data =  (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
// 	for (int i = 0; i < img_height; i++)
// 	{
// 		for (int j = 0; j < img_width; j++)
// 		{
// 			my_image_data[i * img_width + j] = 0X00FF0000;
// 			// my_image_data[j * size_line + i + 1] = 'd';
// 			// my_image_data[j * size_line + i + 2] = 'd';
// 		}
// 	}
// 	mlx_mouse_move(mlx_win, 115, 115);
// 	printf("img_width = %d\n", img_width);
// 	printf("img_height = %d\n", img_height);
// 	printf("bpp = %d\n", bpp);
// 	printf("size_line = %d\n", size_line);
// 	printf("endian = %d\n", endian);
// 	mlx_put_image_to_window(mlx, mlx_win, img, 0, 0);
// 	mlx_loop(mlx);
// 	return (0);
// }