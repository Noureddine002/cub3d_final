/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_up_functs2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:38:28 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/06 20:22:03 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	distancepythagoras(double px, double py, double hitx, double hity)
{
	return (sqrt((hitx - px) * (hitx - px) + (hity - py) * (hity - py)));
}

double	normlize_angle(double r_angle)
{
	r_angle = remainder(r_angle, 2 * M_PI);
	if (r_angle < 0)
		r_angle = (2 * M_PI) + r_angle;
	return (r_angle);
}

void	set_hor_distance(t_ray *ray, t_var *var)
{
	ray->distance_ray = var->hor_hitdis;
	ray->horr_line = 1;
	ray->vert_line = 0;
	var->new_hitx = var->next_x;
	var->new_hity = var->next_y;
}

void	set_vert_distance(t_ray *ray, t_var *var)
{
	ray->distance_ray = var->ver_hitdis;
	ray->vert_line = 1;
	ray->horr_line = 0;
	var->new_hitx = var->next_xv;
	var->new_hity = var->next_yv;
}
