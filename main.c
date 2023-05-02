/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 02:54:54 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/02 22:56:31 by mzridi           ###   ########.fr       */
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

	x *= 32;
	y *= 32;
	block_width = 32;
	block_height = 32;
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
		x = x - (32) + 1;
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
	if (check_wall(data, data->player.v_move_direction, 0))
	{
		data->player.x += data->player.v_move_direction * data->player.dx;
		data->player.y += data->player.v_move_direction * data->player.dy;
	}
	data->player.dx = cos(data->player.angle + M_PI / 2) * MOVE_SPEED;
	data->player.dy = sin(data->player.angle + M_PI / 2) * MOVE_SPEED;
	if (check_wall(data, data->player.h_move_direction, 1))
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
	put_miniplayer(data, &data->player);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	return (0);
}

	// char	*relative_path = "./test.xpm";
	// int		img_width;
	// int		img_height;

	// mlx = mlx_init();
	// img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);

int	main(int ac, char **av)
{
	if (ac != 2) {
    	printf("Usage: %s <map file>\n", av[0]);
    	return 1;
  	}
  	if (is_valid_map(av[1])) {
    	printf("Map is valid.\n");
  	} else {
    	printf("❌ Map is invalid.\n");
  	}
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
// 	char	*relative_path = "./textures/test1337.xpm";
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
// 	printf("img_width = %d\n", img_width);
// 	printf("img_height = %d\n", img_height);
// 	printf("bpp = %d\n", bpp);
// 	printf("size_line = %d\n", size_line);
// 	printf("endian = %d\n", endian);
// 	mlx_put_image_to_window(mlx, mlx_win, img, 0, 0);
// 	mlx_loop(mlx);
// 	return (0);
// }