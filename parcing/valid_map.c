/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 23:04:04 by rel-maza          #+#    #+#             */
/*   Updated: 2023/05/16 23:04:17 by rel-maza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_checkforspaces(t_cub3D *cub)
{
	int	i;
	int	j;

	i = cub->first_line;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
		{
			if (cub->map_arr[i][j] == '0')
			{
				if (cub->map_arr[i][j - 1] == ' ' ||
					cub->map_arr[i][j + 1] == ' ' ||
					cub->map_arr[i - 1][j] == ' ' )
					return (1);
				if (!cub->map_arr[i + 1])
					return (0);
				if (cub->map_arr[i + 1][j] == ' ')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_checkwall(t_cub3D *cub)
{
	int	i;
	int	j;

	j = 0;
	i = cub->first_line ;
	while (cub->map_arr[cub->first_line][j])
	{
		if (cub->map_arr[cub->first_line][j] == '0')
			return (1);
		j++;
	}
	i = cub->first_line;
	while (cub->map_arr[i])
		i++;
	i--;
	j = 0;
	while (cub->map_arr[i][j])
	{
		if (cub->map_arr[i][j] == '0')
			return (1);
		j++;
	}
	return (0);
}

int	check_direction(int i, int j, t_cub3D *cub)
{
	if (check_no(i, j, cub) || check_so(i, j, cub)
		|| check_we(i, j, cub) || check_ea(i, j, cub))
	{
		ft_sortwallpath(i, j, cub);
		return (1);
	}
	else if (cub->map_arr[i][j] == 'F' || cub->map_arr[i][j] == 'C')
	{
		ft_sortcolorpath(i, j, cub);
		return (1);
	}
	return (0);
}

int	init_width_height(t_cub3D *cub)
{
	int	i;
	int	a;
	int	j;

	a = 0;
	i = cub->first_line;
	while (cub->map_arr[i] && cub->map_arr[i][0] != '\n')
	{
		a++;
		i++;
	}
	cub->map_height = a;
	if (a == 0)
		return (1);
	i = cub->first_line;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
			j++;
		if (j > cub->map_width)
			cub->map_width = j;
		i++;
	}
	return (0);
}
