/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:29:45 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/02 23:34:05 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	ft_lsttoarray(t_line *map, t_cub3D *cub)
{
	t_line	*list;
	int		i;
	size_t	len;

	i = 0;
	list = map;
	len = ft_lstsize(list) + 1;
	cub->map_arr = (char **)malloc(sizeof(char *) * len);
	if (!cub->map_arr)
		return ;
	while (list)
	{
		cub->map_arr[i++] = list->line;
		list = list->next;
	}
	cub->map_arr[i] = NULL;
}

char	*rightpad(char *str, int n)
{
	char	*ptr;
	int		i;

	ptr = malloc(n + 1);
	ft_strcpy(ptr, str);
	i = ft_strlen(str) - 1;
	while (i < n)
		ptr[i++] = '+';
	ptr[n] = '\n';
	ptr[n - 1] = '\0';
	return (ptr);
}

void	leftpad(char *str)
{
	while (*str == ' ')
	{
		*str = '+';
		str++;
	}
}

void	fill_map(t_cub3D *cub, t_line *head)
{
	while (head)
	{
		head->line = rightpad(head->line, cub->max_lenght);
		head->line = ft_strjoin(head->line, "\n");
		// printf("%s", head->line);
		head = head->next;
	}
}

int	ft_checkLine(char *line)
{
	int	i;

	i = 0;
	if (line[i] != '1' && line[i] != '0')
		return (1);
	return (0);
}

void	fill_map_back(t_cub3D *cub, t_line *head)
{
	cub->max_lenght = ft_strlen(head->line);
	while (head)
	{
		if (ft_checkLine(head->line))
			leftpad(head->line);
		head = head->next;
	}
}

int	ft_checkForSpaces(t_cub3D *cub)
{
	int	i;
	int	j;

	i = cub->first_line;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
		{
			if (cub->map_arr[i][j] == ' ')
			{
				if (cub->map_arr[i][j - 1] == '0' || cub->map_arr[i][j + 1] == '0' || cub->map_arr[i - 1][j] == '0' || cub->map_arr[i + 1][j] == '0')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_checkWall(t_cub3D *cub)
{
	int	i;
	int	j;

	j = 0;
	while (cub->map_arr[cub->first_line][j])
	{
		if (cub->map_arr[cub->first_line][j] == '0')
			return (1);
		j++;
	}
	i = 0;
	i = cub->first_line;
	while (cub->map_arr[i])
		i++;
	i--;
	j = 0;
	while (cub->map_arr[i][j])
	{
		if (cub->map_arr[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

void	ft_sortPathTexture(t_cub3D *cub)
{
	int	i;

	i = 0;
	while (cub->map_arr[i])
	{
		if (cub->map_arr[i][0] == '\n')
		{
			i++;
			continue ;
		}
		else if (cub->map_arr[i][0] == 'N' && cub->map_arr[i][1] == 'O')
			cub->north_texture = ft_strdup(cub->map_arr[i]);
		else if (cub->map_arr[i][0] == 'S' && cub->map_arr[i][1] == 'O')
			cub->south_texture = ft_strdup(cub->map_arr[i]);
		else if (cub->map_arr[i][0] == 'W' && cub->map_arr[i][1] == 'E')
			cub->west_texture = ft_strdup(cub->map_arr[i]);
		else if (cub->map_arr[i][0] == 'E' && cub->map_arr[i][1] == 'A')
			cub->east_texture = ft_strdup(cub->map_arr[i]);
		else if (cub->map_arr[i][0] == 'F')
			cub->floor_color = ft_strdup(cub->map_arr[i]);
		else if (cub->map_arr[i][0] == 'C')
			cub->ceilling_color = ft_strdup(cub->map_arr[i]);
		else if (cub->map_arr[i][0] == '1' || cub->map_arr[i][0] == ' ')
			break ;
		i++;
	}
}

int	ft_checkIfClosed(t_cub3D *cub, t_line *head)
{
	int i = 0;
	int j = 0;

	while (head)
	{
		if (head->line[0] != '\n' && head->line[0] != 'N' && head->line[0] != 'S' && head->line[0] != 'W' && head->line[0] != 'E' && head->line[0] != 'R' && head->line[0] != 'F' && head->line[0] != 'C')
		{
			cub->first_line = i;
			break;
		}
		head = head->next;
		i++;
		cub->first_line = i;
	}

	i = cub->first_line;
	while (cub->map_arr[i])
	{
		j = 0;
		if (ft_checkWall(cub))
			return 1;
		if(cub->map_arr[i][j] == '0')
			return 1;
		while (cub->map_arr[i][j])
			j++;
		if (cub->map_arr[i][j - 2] != '1')
		{
			printf("Error: map is not closed.\n");
			return 1;
		}
		i++;
	}
	return 0;
}

int is_valid_map( char *filename)
{
	t_var *data;
	t_cub3D *cub = malloc(sizeof(t_cub3D));
	t_line *head = NULL;
	t_line *current = NULL;
	char *line = NULL;
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: could not open file.\n");
		return 0;
	}
	while ((line = get_next_line(fd)))
	{
		t_line *new_node = (t_line *)malloc(sizeof(t_line));
		new_node->line = (char *)malloc(ft_strlen(line) + 1); // +1 for null terminator
		new_node->line = ft_strdup(line);
		new_node->next = NULL;
		if (head == NULL) {
			head = new_node;
			current = new_node;
		} else {
			current->next = new_node;
			current = new_node;
		}
		free(line);
	}
	
	close(fd);
	t_line *tmp = head;
	cub->max_lenght = 0;
	while (tmp)
	{
		if (ft_strlen(tmp->line) > cub->max_lenght)
			cub->max_lenght = ft_strlen(tmp->line);
		tmp = tmp->next;
	}
	tmp = head;
	ft_lsttoarray(head, cub);
	ft_sortPathTexture(cub);
	if (ft_checkIfClosed(cub, tmp))
		return (0);
	fill_map(cub, tmp);
	fill_map_back(cub, tmp);
	if (ft_checkForSpaces(cub))
	{
		printf("Error: map is not closed.\n");
		return (0);
	}
	data = init_data(cub);
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, &key_release, data);
	// mlx_hook(data->mlx_win, 6, 1L << 6, &mouse_move, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
	return 1;
}