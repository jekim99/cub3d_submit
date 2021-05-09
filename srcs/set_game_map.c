/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:14:32 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 15:32:47 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		save_map(char *str, t_cub *cub)
{
	int	len;

	if (cub->cnt != 8)
		return (error_parse_map(1));
	len = ft_strlen(str);
	if (len == 0)
		return (error_parse_map(4));
	cub->map.mapcol++;
	if (len > cub->map.maprowmax)
		cub->map.maprowmax = len;
	cub->map.mapsave = ft_strjoin(cub->map.mapsave, str);
	cub->map.mapsave = ft_strjoin(cub->map.mapsave, "\n");
	if (cub->map.mapcol > 1 && check_map_start(str) == 1)
		cub->map.mapend = 1;
	return (0);
}

void	make_map_row(t_map_pass pass, t_info *info, int **worldmap)
{
	if (ft_isdigit(pass.mapsave))
		worldmap[pass.i][pass.j] = (int)(pass.mapsave - '0');
	else if (pass.mapsave == 'N' || pass.mapsave == 'S'
		|| pass.mapsave == 'W' || pass.mapsave == 'E')
	{
		set_player(pass.mapsave, pass.i, pass.j, info);
		worldmap[pass.i][pass.j] = 8;
	}
	else if (pass.mapsave == ' ')
		worldmap[pass.i][pass.j] = 9;
	else if (pass.mapsave == '\n')
		while (pass.j < pass.maprowmax)
			worldmap[pass.i][pass.j++] = 9;
	else
		error_parse_map(4);
}

int		**make_map(t_map map, t_info *info)
{
	int			**worldmap;
	int			i;
	int			j;
	t_map_pass	pass;

	i = -1;
	pass.maprowmax = map.maprowmax;
	worldmap = (int **)malloc(sizeof(int *) * map.mapcol);
	while (++i < map.mapcol)
	{
		worldmap[i] = (int *)malloc(sizeof(int) * map.maprowmax);
		j = 0;
		if (*map.mapsave == '\n')
			map.mapsave++;
		while (j < map.maprowmax)
		{
			pass.i = i;
			pass.j = j;
			pass.mapsave = *map.mapsave;
			make_map_row(pass, info, worldmap);
			map.mapsave++;
			j++;
		}
	}
	return (worldmap);
}

void	set_player_we(char c, t_info *info)
{
	if (c == 'W')
	{
		info->dir_x = 0;
		info->dir_y = -1;
		info->plane_x = -0.66;
		info->plane_y = 0;
	}
	else if (c == 'E')
	{
		info->dir_x = 0;
		info->dir_y = 1;
		info->plane_x = 0.66;
		info->plane_y = 0;
	}
}

void	set_player(char c, int i, int j, t_info *info)
{
	info->pos_x = i + 0.5;
	info->pos_y = j + 0.5;
	if (c == 'N')
	{
		info->dir_x = -1;
		info->dir_y = 0;
		info->plane_x = 0;
		info->plane_y = 0.66;
	}
	else if (c == 'S')
	{
		info->dir_x = 1;
		info->dir_y = 0;
		info->plane_x = 0;
		info->plane_y = -0.66;
	}
	set_player_we(c, info);
}
