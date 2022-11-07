/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:05:01 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/07 00:34:51 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

unsigned long	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	ray_directions(t_ray *ray)
{
	if (ray->rayang > 0 && ray->rayang < M_PI)
	{
		ray->down_dir = 1;
		ray->up_dir = 0;
	}
	else if (!(ray->rayang > 0 && ray->rayang < M_PI))
	{
		ray->up_dir = 1;
		ray->down_dir = 0;
	}
	if (ray->rayang > M_PI / 2 && (ray->rayang < ((3 * M_PI) / 2)))
	{
		ray->right_dir = 0;
		ray->left_dir = 1;
	}
	else if (!(ray->rayang > M_PI / 2
			&& (ray->rayang < ((3 * M_PI) / 2))))
	{
		ray->right_dir = 1;
		ray->left_dir = 0;
	}
}

void	castallrays(t_map *mapp)
{
	int		i;
	double	ray_angle;

	i = 0;
	ray_angle = mapp->player->rot_nang - (FOV_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		mapp->ray[i].rayang = normlize_angle(ray_angle);
		ray_directions(&mapp->ray[i]);
		mapp->ray[i].column_id = i;
		casting(mapp, mapp->player, &mapp->ray[i]);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}
