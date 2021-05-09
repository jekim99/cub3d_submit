/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_map_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:17:33 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 03:38:38 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	inside_check(t_map map, int **worldmap)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map.mapcol)
	{
		j = 0;
		while (j < map.maprowmax)
		{
			if (worldmap[i][j] == 0)
			{
				if (worldmap[i + 1][j] == 9 || worldmap[i - 1][j] == 9 ||
					worldmap[i][j + 1] == 9 || worldmap[i][j - 1] == 9 ||
					worldmap[i - 1][j - 1] == 9 ||
					worldmap[i - 1][j + 1] == 9 ||
					worldmap[i + 1][j - 1] == 9 || worldmap[i + 1][j + 1] == 9)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	col_check(t_map map, int **worldmap)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < map.maprowmax)
	{
		j = 0;
		while (worldmap[j][i] == 9)
			j++;
		k = map.mapcol - 1;
		while (worldmap[k][i] == 9)
			k--;
		if (worldmap[j][i] != 1 || worldmap[k][i] != 1)
			return (-1);
		if (j > k)
			return (-1);
		i++;
	}
	return (1);
}

int	row_check(t_map map, int **worldmap)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < map.mapcol)
	{
		j = 0;
		while (worldmap[i][j] == 9)
			j++;
		k = map.maprowmax - 1;
		while (worldmap[i][k] == 9)
			k--;
		if (worldmap[i][j] != 1 || worldmap[i][k] != 1)
			return (-1);
		if (j > k)
			return (-1);
		i++;
	}
	return (1);
}

int	map_config_check(t_map map, int **worldmap, t_info *info)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (i < map.mapcol)
	{
		j = 0;
		while (j < map.maprowmax)
		{
			if (worldmap[i][j] == 8)
				p++;
			else if (worldmap[i][j] == 2)
				info->numsprite++;
			j++;
		}
		i++;
	}
	if (p != 1)
		return (-1);
	return (1);
}

int	map_valid_check(t_map map, t_info *info)
{
	int	r;
	int	c;
	int	i;
	int	f;

	r = row_check(map, info->worldmap);
	c = col_check(map, info->worldmap);
	i = inside_check(map, info->worldmap);
	f = map_config_check(map, info->worldmap, info);
	if (r == 1 && c == 1 && i == 1 && f == 1)
		return (1);
	return (-1);
}
