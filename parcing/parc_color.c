/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:43:07 by rel-maza          #+#    #+#             */
/*   Updated: 2023/05/16 22:58:22 by rel-maza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_sortwallpath(int i, int j, t_cub3D *cub)
{
	if (check_no(i, j, cub))
		cub->north_texture = ft_strdup(ft_strtrim(&cub->map_arr[i], "\nNO "));
	else if (check_so(i, j, cub))
		cub->south_texture = ft_strdup(ft_strtrim(&cub->map_arr[i], "\nSO "));
	else if (check_we(i, j, cub))
		cub->west_texture = ft_strdup(ft_strtrim(&cub->map_arr[i], "\nWE "));
	else if (check_ea(i, j, cub))
		cub->east_texture = ft_strdup(ft_strtrim(&cub->map_arr[i], "\nEA "));
}

void	ft_sortcolorpath(int i, int j, t_cub3D *cub)
{
	if (cub->map_arr[i][j] == 'F')
		cub->floor_color = ft_strdup(ft_strtrim(&cub->map_arr[i], "\nF "));
	else if (cub->map_arr[i][j] == 'C')
		cub->ceiling_color = ft_strdup(ft_strtrim(&cub->map_arr[i], "\nC "));
}

int	ft_sortpathtexture(t_cub3D *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map_arr[++i])
	{
		j = 0;
		while (cub->map_arr[i][j] != '\n')
		{
			if (cub->map_arr[i][j] == ' ')
				j++;
			else
			{
				if (check_direction(i, j, cub))
					break ;
				else if (cub->map_arr[i][j] == '1' || \
					cub->map_arr[i][j] == '0' || cub->map_arr[i][j] == ' ')
					break ;
				else
					return (1);
				break ;
			}
		}
	}
	return (0);
}

int	convert_floor_color(t_cub3D *cub)
{
	cub->floor_color_int = malloc(sizeof(int) * 3);
	cub->floor_color_int[0] = ft_atoi(cub->floor_color_r);
	cub->floor_color_int[1] = ft_atoi(cub->floor_color_g);
	cub->floor_color_int[2] = ft_atoi(cub->floor_color_b);
	if (cub->floor_color_int[0] > 255 || cub->floor_color_int[1] > 255
		|| cub->floor_color_int[2] > 255)
	{
		printf("Error: wrong color format.\n");
		return (1);
	}
	if (cub->floor_color_int[0] < 0 || cub->floor_color_int[1] < 0
		|| cub->floor_color_int[2] < 0)
	{
		printf("Error: wrong color format.\n");
		return (1);
	}
	return (0);
}

int	convert_ceiling_color(t_cub3D *cub)
{
	cub->ceiling_color_int = malloc(sizeof(int) * 3);
	cub->ceiling_color_int[0] = ft_atoi(cub->ceiling_color_r);
	cub->ceiling_color_int[1] = ft_atoi(cub->ceiling_color_g);
	cub->ceiling_color_int[2] = ft_atoi(cub->ceiling_color_b);
	if (cub->ceiling_color_int[0] > 255 || cub->ceiling_color_int[1] > 255
		|| cub->ceiling_color_int[2] > 255)
	{
		printf("Error: wrong color format.\n");
		return (1);
	}
	if (cub->ceiling_color_int[0] < 0 || cub->ceiling_color_int[1] < 0
		|| cub->ceiling_color_int[2] < 0)
	{
		printf("Error: wrong color format.\n");
		return (1);
	}
	return (0);
}
