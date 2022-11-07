/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 00:00:24 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/07 19:23:37 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_six_lines(char *s)
{
	if (s[0] == 'N' && s[1] == 'O' && s[2] == ' ')
		return (1);
	else if (s[0] == 'S' && s[1] == 'O' && s[2] == ' ')
		return (1);
	else if (s[0] == 'W' && s[1] == 'E' && s[2] == ' ')
		return (1);
	else if (s[0] == 'E' && s[1] == 'A' && s[2] == ' ')
		return (1);
	else if (s[0] == 'F' && s[1] == ' ')
		return (1);
	else if (s[0] == 'C' && s[1] == ' ')
		return (1);
	else
		return (0);
}

int	check_duplicate_direction(char **sixlines)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (sixlines[i])
	{
		j = i + 1;
		while (sixlines[j])
		{
			if (!ft_strncmp(sixlines[i], sixlines[j], 2))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_xpm_files(char **sixlines)
{
	int		i;
	char	*s;
	int		j;

	i = 0;
	while (sixlines[i])
	{
		j = 0;
		if (!ft_strchr(sixlines[i], ','))
		{
			s = ft_strchr(sixlines[i], ' ');
			if (s[j] == ' ')
				while (s[j] == ' ')
					++s;
			if (open(s, O_RDWR, 777) == -1
				|| ft_strcmp(ft_strrchr(s, '.'), ".xpm") != 0)
				return (0);
			i++;
		}
		else
			i++;
	}
	return (1);
}
