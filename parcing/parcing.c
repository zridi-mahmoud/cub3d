/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:29:45 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/16 23:05:30 by rel-maza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_utils(t_cub3D *cub, int i, int j)
{
	while (cub->map_arr[i])
	{
		j = 0;
		if (ft_checkwall(cub))
			return (1);
		if (cub->map_arr[i][j] == '0')
			return (1);
		while (cub->map_arr[i][j])
			j++;
		if (j >= 2)
		{
			if (cub->map_arr[i][j - 2] == '0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_checkifclosed(t_cub3D *cub, t_line *head)
{
	int	i;
	int	j;

	i = 0;
	while (head)
	{
		j = 0;
		while (head->line[j] && head->line[j] == ' ')
			j++;
		if (head->line[j] == '0' || head->line[j] == '1')
		{
			cub->first_line = i;
			break ;
		}
		head = head->next;
		i++;
		cub->first_line = i;
	}
	if (init_width_height(cub))
		return (1);
	i = cub->first_line;
	if (check_utils(cub, i, j))
		return (1);
	return (0);
}

int	ft_checkformultiplemap(t_cub3D *cub)
{
	int	i;
	int	j;
	int	a;
	int	map_height;

	a = 0;
	map_height = cub->map_height;
	i = cub->first_line;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
		{
			if (cub->map_arr[i][j] == '1' || cub->map_arr[i][j] == '0')
			{
				a++;
				break ;
			}
			j++;
		}
		i++;
	}
	if (map_height != a)
		return (1);
	return (0);
}

int	ft_checkcolor(char *str)
{
	int	i;
	int	a;

	a = 0;
	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == ',')
		{
			a++;
			i++;
		}
		if (!ft_isdigit(str[i]))
		{
			printf("Error: wrong color format.\n");
			return (1);
		}
		i++;
	}
	if (a != 2)
		return (1);
	return (0);
}

int	ft_colorparce(t_cub3D *cub)
{
	char	**arr;
	char	**arr2;

	if (ft_checkcolor(cub->floor_color) || ft_checkcolor(cub->ceiling_color))
		return (1);
	arr = ft_split(cub->floor_color, ',');
	arr2 = ft_split(cub->ceiling_color, ',');
	cub->floor_color_r = arr[0];
	cub->floor_color_g = arr[1];
	cub->floor_color_b = arr[2];
	cub->ceiling_color_r = arr2[0];
	cub->ceiling_color_g = arr2[1];
	cub->ceiling_color_b = arr2[2];
	if (convert_floor_color(cub) || convert_ceiling_color(cub))
		return (1);
	return (0);
}
