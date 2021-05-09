/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:22:21 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 14:10:20 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_texture_cast(t_wall *wall, t_info *info, int x)
{
	int		y;
	int		color;

	y = wall->dstart;
	while (y < wall->dend)
	{
		wall->tex_y = (int)wall->texpos & (TEXHEIGHT - 1);
		wall->texpos += wall->steptex;
		color = info->texture[wall->texnum]
							[TEXHEIGHT * wall->tex_y + wall->tex_x];
		info->buff[y][x] = color;
		y++;
	}
}

void	wall_casting(t_info *info)
{
	int		x;
	t_wall	wall;

	x = 0;
	while (x < info->width)
	{
		wall_calc(x, &wall, info);
		wall_dda(&wall, info);
		wall_dist(&wall, info);
		wall_texture(&wall, info);
		wall.steptex = 1.0 * TEXHEIGHT / wall.lineh;
		wall.texpos = (wall.dstart + (wall.lineh - info->height) / 2)
			* wall.steptex;
		wall_texture_cast(&wall, info, x);
		info->zbuff[x] = wall.pwalldist;
		x++;
	}
}
