/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:55:42 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/30 15:11:03 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
#include <fcntl.h>
# define FOV 1.0472
# define WINDOW_HEIGHT 720
# define WINDOW_WIDTH 1280
# define MAP_WIDTH 15
# define MAP_HEIGHT 10
# define MINIMAP_HEIGHT 100
# define MINIMAP_WIDTH 200
# define MOVE_SPEED 5
# define ROTATION_SPEED 0.05
# define SKY_COLOR 0x00BFFF
# define GROUND_COLOR 0x8B4513
# define WALL_COLOR_D 0x0000FF
# define WALL_COLOR_U 0xFF0000
# define WALL_COLOR_L 0x00FF00
# define WALL_COLOR_R 0xFFFF00

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_point {
	double	x;
	double	y;
}	t_point;

typedef struct s_ray {
	double	x;
	double	y;
	double	angle;
	double	dx;
	double	dy;
	char	type;
	t_point	wall;
}				t_ray;

typedef struct s_player {
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	angle;
	int		v_move_direction;
	int		h_move_direction;
	int		rotation_direction;
	int		last_mouse_x;
	int		mouse_x;
}				t_player;

typedef struct s_var {
	t_data		img;
	t_player	player;
	char		**map;
	void		*mlx;
	void		*mlx_win;
}	t_var;

typedef struct s_line
{
    char *line;
    struct s_line *next;
}t_line;


typedef struct cub3D_s
{
    int width;
    int height;
    int max_lenght;
    char **map_arr;
    t_line  *head;
    int first_line;
} t_cub3D;

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
int		render_next_frame(t_var *data);
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
char	get_map_value(t_var *data, t_point point);
int		key_release(int keycode, t_var *data);
int		mouse_move(int x, int y, t_var *data);
//parce
char	*get_next_line(int fd);
char	*ft_strjoin(char  *s1, char  *s2);
char	*ft_strtrim(char **s1, char  *set);
int		ft_strlen(char *s);
char	*get_line(int fd);
int		ft_lstsize(t_line *lst);
void	ft_lsttoarray(t_line *map, t_cub3D *cub);
char	*rightpad(char *str, int n);
void	leftpad(char *str);
void	fill_map(t_cub3D *cub, t_line *head);
int		ft_checkLine(char *line);
void	fill_map_back(t_cub3D *cub, t_line *head);
int		ft_checkForSpaces(t_cub3D *cub);
int		ft_checkWall(t_cub3D *cub);
int		ft_checkIfClosed(t_cub3D *cub, t_line *head);
int		is_valid_map( char *filename);
int		parcing(int argc, char *argv[]);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(char *src);
// static int	ft_count(char *dest);
char	*ft_strcat(char *dest, char *src);
// static int	min(size_t a, size_t b);
char	*ft_substr(char *s, unsigned int start, size_t len);
// static int	ft_check(char const *set, char c);
char	*ft_strtrim(char **s1, char *set);
#endif