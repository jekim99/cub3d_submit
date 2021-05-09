/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_config_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:04:30 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/08 14:43:25 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_start(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (-1);
	while (str[i])
	{
		if (!ft_isspace(str[i]) && str[i] != '1')
			return (-1);
		i++;
	}
	return (1);
}

int	check_doup_conf(int identifier, t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->cnt)
	{
		if (cub->save[i] == identifier)
			return (-1);
		i++;
	}
	if (cub->cnt >= 8)
		return (-1);
	return (1);
}

int	check_str_remain(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

int	check_split(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	if (count == 2)
		return (1);
	else
		return (0);
}
