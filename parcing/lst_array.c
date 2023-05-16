/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:32:59 by rel-maza          #+#    #+#             */
/*   Updated: 2023/05/16 22:33:57 by rel-maza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_checkline(char	*line)
{
	int	i;

	i = 0;
	if (line[i] != '1' && line[i] != '0')
		return (1);
	return (0);
}

int	ft_lstsize(t_line *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

int	ft_lsttoarray(t_line *map, t_cub3D *cub)
{
	t_line	*list;
	int		i;
	size_t	len;

	i = 0;
	list = map;
	len = ft_lstsize(list) + 1;
	if (len == 1)
	{
		printf("Error : empty file.cub\n");
		return (1);
	}
	cub->map_arr = (char **)malloc(sizeof(char *) * len);
	if (!cub->map_arr)
		return (0);
	while (list)
	{
		cub->map_arr[i++] = list->line;
		list = list->next;
	}
	cub->map_arr[i] = NULL;
	return (0);
}
