/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:29:45 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/16 17:03:02 by rel-maza         ###   ########.fr       */
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
		head->line = rightpad(head->line, cub->max_lenght);
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

int	ft_checkWall(t_cub3D *cub)
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

int check_No(int i, int j, t_cub3D *cub)
{
	if (cub->map_arr[i][j] == 'N' && cub->map_arr[i][j + 1] == 'O')
		return (1);
	return (0);
}

int check_So(int i, int j, t_cub3D *cub)
{
	if (cub->map_arr[i][j] == 'S' && cub->map_arr[i][j + 1] == 'O')
		return (1);
	return (0);
}

int check_We(int i, int j, t_cub3D *cub)
{
	if (cub->map_arr[i][j] == 'W' && cub->map_arr[i][j + 1] == 'E')
		return (1);
	return (0);
}

int check_Ea(int i, int j, t_cub3D *cub)
{
	if (cub->map_arr[i][j] == 'E' && cub->map_arr[i][j + 1] == 'A')
		return (1);
	return (0);
}

int ft_countPathTexture(t_cub3D *cub)
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
				if (check_No(i, j, cub) || check_So(i, j, cub)
					|| check_We(i, j, cub) || check_Ea(i, j, cub)
					|| cub->map_arr[i][j] == 'F' || cub->map_arr[i][j] == 'C')
					count++;
				j++;
			}
		}
		i++;
	}
	return (count != 6);
}

void ft_sortWallPath(int i, int j, t_cub3D *cub)
{
	if (check_No(i, j, cub))
		cub->north_texture = ft_strdup(ft_strtrim(&cub->map_arr[i], "\nNO "));
	else if (check_So(i, j, cub))
		cub->south_texture = ft_strdup(ft_strtrim(&cub->map_arr[i], "\nSO "));
	else if (check_We(i, j, cub))
		cub->west_texture = ft_strdup(ft_strtrim(&cub->map_arr[i], "\nWE "));
	else if (check_Ea(i, j, cub))
		cub->east_texture = ft_strdup(ft_strtrim(&cub->map_arr[i], "\nEA "));
}

void ft_sortColorPath(int i, int j, t_cub3D *cub)
{
	if (cub->map_arr[i][j] == 'F')
		cub->floor_color = ft_strdup(ft_strtrim(&cub->map_arr[i], "\nF "));
	else if (cub->map_arr[i][j] == 'C')
		cub->ceiling_color = ft_strdup(ft_strtrim(&cub->map_arr[i], "\nC "));
}

int check_direction(int i, int j, t_cub3D *cub)
{
	if (check_No(i, j, cub) || check_So(i, j, cub) || check_We(i, j, cub) || check_Ea(i, j, cub))
	{
		ft_sortWallPath(i, j, cub);
		return (1);
	}
	else if (cub->map_arr[i][j] == 'F' || cub->map_arr[i][j] == 'C')
	{
		ft_sortColorPath(i, j, cub);
		return (1);
	}
	return (0);
}

int	ft_sortPathTexture(t_cub3D *cub)
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

int init_width_height(t_cub3D *cub)
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

int	check_utils(t_cub3D *cub, int i, int j)
{
	while (cub->map_arr[i])
	{
		j = 0;
		if (ft_checkWall(cub))
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

int	ft_checkIfClosed(t_cub3D *cub, t_line *head)
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

int ft_checkForMultipleMap(t_cub3D *cub)
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

int ft_findPlayer(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int ft_checkPlayerRow(int i, int j, t_cub3D *cub)
{
	if ((cub->map_arr[i - 1][j] != '1' && cub->map_arr[i - 1][j] != '0' ) ||
		(cub->map_arr[i + 1][j] != '1' && cub->map_arr[i + 1][j] != '0' ))
		return (1);
	return (0);
}

int ft_checkPlayerColumn(int i, int j, t_cub3D *cub)
{
	if ((cub->map_arr[i][j - 1] != '1' && cub->map_arr[i][j - 1] != '0' ) ||
		(cub->map_arr[i][j + 1] != '1' && cub->map_arr[i][j + 1] != '0' ))
		return (1);
	return (0);
}

int ft_check_position(t_cub3D *cub)
{
	int	i;
	int	j;

	i = cub->first_line;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
		{
			if (ft_findPlayer(cub->map_arr[i][j]))
			{
				if (i == cub->first_line || i == cub->map_height
					+ cub->first_line - 1 || j == 0 || j == cub->map_width)
					return (1);
				if (ft_checkPlayerRow(i, j, cub)
					|| ft_checkPlayerColumn(i, j, cub))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int ft_checkForPlayer(t_cub3D	*cub)
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
			if (ft_findPlayer(cub->map_arr[i][j]))
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

int convert_ceiling_color(t_cub3D *cub)
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

int ft_checkColor(char *str)
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

int	ft_colorParce(t_cub3D *cub)
{
	char	**arr;
	char	**arr2;

	if (ft_checkColor(cub->floor_color) || ft_checkColor(cub->ceiling_color))
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

void	ft_print_map(t_cub3D *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
		{
			printf("%c", cub->map_arr[i][j]);
			j++;
		}
		i++;
	}
}

void	check_file(char *filename, t_cub3D *cub)
{
	cub->fd = open(filename, O_RDONLY);
	if (cub->fd == -1)
	{
		printf("Error: could not open file.\n");
		exit(1);
	}
}

void	check_forma(t_cub3D *cub, t_line *tmp)
{
	if (ft_sortPathTexture(cub) || ft_checkIfClosed(cub, tmp))
	{
		printf("Error: ddewdwedwedwedwedwdwed.\n");
		exit(0);
	}
	if (ft_checkForMultipleMap(cub))
	{
		printf("Error: multiple maps.\n");
		exit(0);
	}
	if (ft_checkForSpaces(cub) || ft_countPathTexture(cub) || \
		ft_checkForPlayer(cub) || ft_colorParce(cub))
	{
		printf("Error: map is not cdlosed.\n");
		exit(0);
	}
}

void hooks(t_var *data)
{
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, &key_release, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
}

t_line 	*read_map(t_cub3D *cub)
{
	t_line	*new_node;
	t_line	*current;
	t_line 	*head = NULL;
	char	*line;

	while ((line = get_next_line(cub->fd)))
	{
		new_node = (t_line *)malloc(sizeof(t_line));
		new_node->line = ft_strdup(line);
		new_node->next = NULL;
		if (head == NULL)
		{
			head = new_node;
			current = new_node;
		}
		else
		{
			current->next = new_node;
			current = new_node;
		}
		free(line);
	}
	close(cub->fd);
	return (head);
}

int filling(t_cub3D *cub, t_line *tmp)
{
	fill_map(cub, tmp);
	fill_map_back(cub, tmp);
	if (ft_lsttoarray(tmp, cub))
		return (0);
	check_forma(cub, tmp);
	return (1);
}

int  is_valid_map( char *filename)
{
	t_var	*data;
	t_cub3D	*cub;
	t_line	*head;
	t_line	*tmp;

	data = malloc(sizeof(t_var));
	cub = malloc(sizeof(t_cub3D));
	check_file(filename, cub);
	head = read_map(cub);
	tmp = head;
	cub->max_lenght = 0;
	while (tmp)
	{
		if (ft_strlen(tmp->line) > cub->max_lenght)
			cub->max_lenght = ft_strlen(tmp->line);
		tmp = tmp->next;
	}
	tmp = head;
	if (!filling(cub, tmp))
		return (0);
	data = init_data(cub);
	if (data == NULL)
		return (1);
	hooks(data);
	return (1);
}
