/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_struct_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 00:11:50 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/06 00:11:51 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	initialize_colors(char **map, char *s, int i, t_map *test)
{
	char	**t;

	if (map[i][0] == 'F')
	{
		s = ft_strrchr(map[i], ' ');
		t = ft_split(s, ',');
		test->colors->floor[0] = ft_atoi(t[0]);
		test->colors->floor[1] = ft_atoi(t[1]);
		test->colors->floor[2] = ft_atoi(t[2]);
		ft_free_str_map(NULL, t);
	}
	else
	{
		s = ft_strrchr(map[i], ' ');
		t = ft_split(s, ',');
		test->colors->ceilling[0] = ft_atoi(t[0]);
		test->colors->ceilling[1] = ft_atoi(t[1]);
		test->colors->ceilling[2] = ft_atoi(t[2]);
		ft_free_str_map(NULL, t);
	}
}

void	initialize_textures(char **map, char *s, int i, t_map *test)
{
	if (map[i][0] == 'N' && map[i][1] == 'O')
	{
		s = ft_strrchr(map[i], ' ');
		s++;
		test->txt_no = ft_strdup(s);
	}
	if (map[i][0] == 'S' && map[i][1] == 'O')
	{
		s = ft_strrchr(map[i], ' ');
		s++;
		test->txt_so = ft_strdup(s);
	}
	if (map[i][0] == 'W' && map[i][1] == 'E')
	{
		s = ft_strrchr(map[i], ' ');
		s++;
		test->txt_we = ft_strdup(s);
	}
	if (map[i][0] == 'E' && map[i][1] == 'A')
	{
		s = ft_strrchr(map[i], ' ');
		s++;
		test->txt_ea = ft_strdup(s);
	}
}

void	initialize_strct(char **map, char player, t_map *test)
{
	int		i;
	char	*s;

	i = -1;
	s = NULL;
	test->gamer = player;
	while (map[++i])
	{
		if (ft_strchr(map[i], ','))
			initialize_colors(map, s, i, test);
		else
			initialize_textures(map, s, i, test);
	}
}
