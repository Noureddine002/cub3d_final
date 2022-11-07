/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 00:29:10 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/07 03:30:30 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_wall(t_map *m, int x, int y, char identf)
{
	int	grid_x;
	int	grid_y;

	grid_x = floor(x / TILESIZE);
	grid_y = floor(y / TILESIZE);
	if (grid_x >= m->map_width_x || grid_y >= m->map_height_y)
		return (1);
	if (m->map_grid[grid_y][grid_x] == identf)
		return (1);
	return (0);
}
