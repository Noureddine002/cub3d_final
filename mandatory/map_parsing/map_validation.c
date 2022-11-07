/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 23:59:44 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/06 00:03:50 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_colors_utils(char *s, int *k)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] != ',' && !ft_isdigit(s[i]))
			return (0);
		if (s[i] == ',')
			(*k)++;
		i++;
	}
	if (s[i] == ' ')
		return (0);
	return (1);
}

int	check_colors(char **sixlines, int i, int k, int j)
{
	char	**tmp;
	char	*str;

	while (sixlines[++i])
	{
		if (ft_strchr(sixlines[i], ','))
		{
			str = ft_strchr(sixlines[i], ' ');
			++str;
			if (!check_colors_utils(str, &k))
				return (0);
			if (k != 2)
				return (0);
			k = 0;
			tmp = ft_split(str, ',');
			j = -1;
			while (tmp[++j])
				if (ft_atoi(tmp[j]) > 255 || ft_atoi(tmp[j]) < 0)
					return (0);
			ft_free_str_map(NULL, tmp);
			if (j != 3)
				return (0);
		}
	}
	return (1);
}

int	check_player(char **map, int i)
{
	int	j;
	int	p;

	p = 0;
	while (map[i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' \
				|| map[i][j] == 'E' || map[i][j] == 'W')
					p++;
		}
		i++;
	}
	if (p != 1)
		return (0);
	return (1);
}

int	check_player_map_elems(char **map, int i, char *p)
{
	int	j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' \
			&& map[i][j] != 'N' && map[i][j] != 'S' \
			&& map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != ' ')
				return (0);
			if (map[i][j] == 'N' || map[i][j] == 'S' \
				|| map[i][j] == 'E' || map[i][j] == 'W')
				*p = map[i][j];
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_utils(char **map, int i, int j, char p)
{
	if (map[i][j + 1] != '1' && map[i][j + 1] != '0' \
		&& map[i][j + 1] != p)
		return (0);
	if (map[i][j - 1] != '1' && map[i][j - 1] != '0' \
		&& map[i][j - 1] != p)
		return (0);
	if (map[i + 1][j] != '1' && map[i + 1][j] != '0' \
		&& map[i + 1][j] != p)
		return (0);
	if (map[i - 1][j] != '1' && map[i - 1][j] != '0' \
		&& map[i - 1][j] != p)
		return (0);
	return (1);
}
