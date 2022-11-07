/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 19:24:25 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/06 19:35:36 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	get_map_width(char **map)
{
	int	i;
	int	j;

	i = 6;
	j = (int)ft_strlen(map[i]);
	while (map[i])
	{
		if (j < (int)ft_strlen(map[i]))
			j = (int)ft_strlen(map[i]);
		i++;
	}
	return (j);
}

int	get_map_height(char **map)
{
	int	i;

	i = 1;
	while (map[i])
		i++;
	return (i);
}

void	fill_grid_map(t_map *test, char **map, int *b, char **grid)
{
	int	i;
	int	j;

	i = 5;
	while (map[++i])
	{
		j = -1;
		grid[*b] = malloc(sizeof(char) * test->map_width_x + 1);
		if (!grid[*b])
			ft_allocation_err();
		while (map[i][++j])
		{
			grid[*b][j] = map[i][j];
			if (grid[*b][j] == ' ')
				grid[*b][j] = '1';
		}
		if (test->map_width_x > j)
		{
			while (test->map_width_x > j)
				grid[*b][j++] = '1';
		}
		grid[*b][j] = '\0';
		*b += 1;
	}
	grid[*b] = NULL;
}

char	**true_map(t_map *test, char **map)
{
	char	**grid;
	int		i;

	i = 0;
	test->map_width_x = get_map_width(map);
	test->map_height_y = get_map_height(map) - 6;
	grid = malloc(sizeof(char *) * test->map_height_y + 1);
	if (!grid)
		ft_allocation_err();
	fill_grid_map(test, map, &i, grid);
	ft_free_str_map(NULL, map);
	return (grid);
}
