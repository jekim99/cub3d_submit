/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:20:07 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/08 23:29:35 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_casting(t_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < (info->height / 2))
	{
		x = 0;
		while (x < info->width)
		{
			info->buff[y][x] = info->color[0];
			x++;
		}
		y++;
	}
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			info->buff[y][x] = info->color[1];
			x++;
		}
		y++;
	}
}
