/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:55:42 by mzridi            #+#    #+#             */
/*   Updated: 2023/04/02 20:57:40 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

char	map[10][15] = {
	"111111111111111",
	"1000W0000000001",
	"101110111011101",
	"101110111011101",
	"101110111011101",
	"101110111011101",
	"101110111011101",
	"100000000000001",
	"100000000000001",
	"111111111111111"
};

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
	void		*mlx;
	void		*mlx_win;
}	t_var;

const int	window_width = 720;
const int	window_height = 480;
const int	map_width = 15;
const int	map_height = 10;

#endif