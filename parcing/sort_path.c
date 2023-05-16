/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:36:10 by rel-maza          #+#    #+#             */
/*   Updated: 2023/05/16 22:56:26 by rel-maza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_no(int i, int j, t_cub3D *cub)
{
	if (cub->map_arr[i][j] == 'N' && cub->map_arr[i][j + 1] == 'O')
		return (1);
	return (0);
}

int	check_so(int i, int j, t_cub3D *cub)
{
	if (cub->map_arr[i][j] == 'S' && cub->map_arr[i][j + 1] == 'O')
		return (1);
	return (0);
}

int	check_we(int i, int j, t_cub3D *cub)
{
	if (cub->map_arr[i][j] == 'W' && cub->map_arr[i][j + 1] == 'E')
		return (1);
	return (0);
}

int	check_ea(int i, int j, t_cub3D *cub)
{
	if (cub->map_arr[i][j] == 'E' && cub->map_arr[i][j + 1] == 'A')
		return (1);
	return (0);
}

int	ft_countpathtexture(t_cub3D *cub)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j] != '\n')
		{
			if (cub->map_arr[i][j] == ' ')
				j++;
			else
			{
				if (check_no(i, j, cub) || check_so(i, j, cub)
					|| check_we(i, j, cub) || check_ea(i, j, cub)
					|| cub->map_arr[i][j] == 'F' || cub->map_arr[i][j] == 'C')
					count++;
				j++;
			}
		}
		i++;
	}
	return (count != 6);
}
