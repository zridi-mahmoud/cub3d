/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:54:38 by rel-maza          #+#    #+#             */
/*   Updated: 2023/05/16 22:59:05 by rel-maza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_findplayer(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	ft_checkplayerrow(int i, int j, t_cub3D *cub)
{
	if ((cub->map_arr[i - 1][j] != '1' && cub->map_arr[i - 1][j] != '0' ) ||
		(cub->map_arr[i + 1][j] != '1' && cub->map_arr[i + 1][j] != '0' ))
		return (1);
	return (0);
}

int	ft_checkplayercolumn(int i, int j, t_cub3D *cub)
{
	if ((cub->map_arr[i][j - 1] != '1' && cub->map_arr[i][j - 1] != '0' ) ||
		(cub->map_arr[i][j + 1] != '1' && cub->map_arr[i][j + 1] != '0' ))
		return (1);
	return (0);
}

int	ft_check_position(t_cub3D *cub)
{
	int	i;
	int	j;

	i = cub->first_line;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
		{
			if (ft_findplayer(cub->map_arr[i][j]))
			{
				if (i == cub->first_line || i == cub->map_height
					+ cub->first_line - 1 || j == 0 || j == cub->map_width)
					return (1);
				if (ft_checkplayerrow(i, j, cub)
					|| ft_checkplayercolumn(i, j, cub))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_checkforplayer(t_cub3D	*cub)
{
	int	i;
	int	j;
	int	a;

	a = 0;
	i = cub->first_line;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
		{
			if (ft_findplayer(cub->map_arr[i][j]))
				a++;
			else if (cub->map_arr[i][j] != '1' && cub->map_arr[i][j]
				!= '0' && cub->map_arr[i][j]
				!= ' ' && cub->map_arr[i][j] != '\n')
				return (1);
			j++;
		}
		i++;
	}
	if (a != 1)
		return (1);
	return (ft_check_position(cub));
}
