/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:55:42 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/26 11:26:16 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# define FOV 1.0472
# define WINDOW_HEIGHT 480
# define WINDOW_WIDTH 1280
# define MAP_WIDTH 15
# define MAP_HEIGHT 10
# define MINIMAP_HEIGHT 100
# define MINIMAP_WIDTH 200
# define MOVE_SPEED 0.1
# define ROTATION_SPEED 0.1
# define SKY_COLOR 0x00BFFF
# define GROUND_COLOR 0x8B4513
# define WALL_COLOR 0x00A0A0

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_ray {
	double	x;
	double	y;
	double	angle;
	double	dx;
	double	dy;
	char	type;
}				t_ray;

typedef struct s_player {
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	angle;
}				t_player;

typedef struct s_var {
	t_data		img;
	t_player	player;
	char		**map;
	void		*mlx;
	void		*mlx_win;
}	t_var;

typedef struct s_point {
	double	x;
	double	y;
}	t_point;

void	init_player(t_player *player, int i, int j, char dir);
t_var	*init_data(char **map);
int		check_wall(t_var *data, int i);
int		key_press(int keycode, t_var *data);
int		to_minmap(int x, int y);
void	put_miniplayer(t_data *data, t_player *player);
void	draw_minimap(t_var *data);
void	put_block_mini(t_data *data, int x, int y, int color);
void	draw_rays(t_var *data);
void	draw_ray(t_var *data, t_ray *ray);
void	render_next_frame(t_var *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_point	first_h_inter(t_var *data, t_ray *ray);
t_point	ith_h_inter(t_var *data, t_ray *ray, int i);
t_point	ith_v_inter(t_var *data, t_ray *ray, int i);
t_point	dist_to_h_wall(t_var *data, t_ray *ray);
t_point	dist_to_v_wall(t_var *data, t_ray *ray);
double	distance_wall(t_var *data, t_ray *ray);
void	draw_3d(t_var *data);
int		is_facing_up(float angle);
int		is_facing_left(float angle);
void	put_point(t_data *data, int x, int y, int color);

#endif