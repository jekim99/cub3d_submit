/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:16:25 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/08 23:55:07 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_spi	*make_sprite_info(t_map map, t_info *info)
{
	t_spi	*spi;
	int		x;
	int		y;
	int		i;

	x = 0;
	i = 0;
	spi = (t_spi *)malloc(sizeof(t_spi) * info->numsprite);
	while (x < map.mapcol)
	{
		y = 0;
		while (y < map.maprowmax)
		{
			if (info->worldmap[x][y] == 2)
			{
				spi[i].x = x + 0.5;
				spi[i].y = y + 0.5;
				spi[i].spritedist = 0;
				i++;
			}
			y++;
		}
		x++;
	}
	return (spi);
}
