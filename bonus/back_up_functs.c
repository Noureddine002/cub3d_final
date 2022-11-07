/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_up_functs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:38:33 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/07 03:17:08 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_square(int x, int y, char c, t_img *img)
{
	int	i;
	int	j;
	int	color;

	if (c == '0')
		color = 0xffffff;
	else if (c == '1')
		color = 0x000000;
	else if (c == 'p')
		color = 0x008000;
	j = y;
	while (j < y + (TILESIZE * 0.2))
	{
		i = x;
		while (i < x + (TILESIZE * 0.2))
		{
			set_screen_pixel(img, i, j, color);
			i++;
		}
		j++;
	}
}
