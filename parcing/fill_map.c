/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:48:34 by rel-maza          #+#    #+#             */
/*   Updated: 2023/05/16 23:52:53 by rel-maza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*rightpad(char *str, int n)
{
	char	*ptr;
	int		i;

	ptr = malloc(n + 1);
	ft_strcpy(ptr, str);
	i = ft_strlen(str) - 1 ;
	while (i < n)
		ptr[i++] = ' ';
	ptr[n - 1] = '\n';
	ptr[n] = '\0';
	return (ptr);
}

void	leftpad(char *str)
{
	while (*str == ' ')
	{
		*str = ' ';
		str++;
	}
}

void	fill_map(t_cub3D *cub, t_line *head)
{
	while (head)
	{
		head->line = ft_strjoin(head->line, "\n");
		head->line = rightpad(head->line, cub->max_lenght + 1);
		head = head->next;
	}
}

void	fill_map_back(t_cub3D *cub, t_line *head)
{
	cub->max_lenght = ft_strlen(head->line);
	while (head)
	{
		if (ft_checkline(head->line))
			leftpad(head->line);
		head = head->next;
	}
}

int	filling(t_cub3D *cub, t_line *tmp)
{
	fill_map(cub, tmp);
	fill_map_back(cub, tmp);
	if (ft_lsttoarray(tmp, cub))
		return (0);
	check_forma(cub, tmp);
	return (1);
}
