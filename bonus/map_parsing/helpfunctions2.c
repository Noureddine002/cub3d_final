/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpfunctions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 00:07:16 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/06 00:07:26 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

size_t	ft_strlen(const	char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	k;
	size_t	a;
	char	*str;

	i = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	a = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((a + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (s1 && s2)
	{
		while (s1[i])
			str[k++] = s1[i++];
		i = 0;
		while (s2[i])
			str[k++] = s2[i++];
		free((char *)s1);
		str[k] = '\0';
		return (str);
	}
	return (NULL);
}

void	ft_allocation_err(void)
{
	write(2, "error in allocation\n", 20);
	exit(1);
}

char	**ft_free_str_map(char *s, char **map)
{
	int	i;

	i = 0;
	if (s)
		free(s);
	while (map[i])
		free(map[i++]);
	free(map);
	return (NULL);
}
