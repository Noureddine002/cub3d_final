/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 00:24:30 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/06 00:24:31 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_extension(char *str)
{
	size_t	i;
	char	*s;
	int		cont;

	s = str;
	i = 0;
	cont = 0;
	while (s[i])
	{
		if (s[i] == '.')
			cont++;
		i++;
	}
	if (cont != 1)
		return (0);
	i = ft_strlen(str);
	if (!str || i < 5)
		return (0);
	if (ft_strcmp(str + (i - 4), ".cub") == 0)
		return (1);
	return (0);
}
