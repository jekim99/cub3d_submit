/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen_wall_calc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:23:40 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 14:09:40 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_calc(int x, t_wall *wall, t_info *info)
{
	wall->camera_x = (2 * x / (double)info->width) - 1;
	wall->raydir_x = info->dir_x + info->plane_x * wall->camera_x;
	wall->raydir_y = info->dir_y + info->plane_y * wall->camera_x;
	wall->map_x = (int)info->pos_x;
	wall->map_y = (int)info->pos_y;
	wall->deldistx = sqrt(1 + pow(wall->raydir_y, 2) / pow(wall->raydir_x, 2));
	wall->deldisty = sqrt(1 + pow(wall->raydir_x, 2) / pow(wall->raydir_y, 2));
	wall->hit = 0;
	wall_set_step(wall, info);
}

void	wall_set_step(t_wall *wall, t_info *info)
{
	if (wall->raydir_x < 0)
	{
		wall->stepx = -1;
		wall->sidedistx = (info->pos_x - wall->map_x) * wall->deldistx;
	}
	else
	{
		wall->stepx = 1;
		wall->sidedistx = (wall->map_x - info->pos_x + 1.0) * wall->deldistx;
	}
	if (wall->raydir_y < 0)
	{
		wall->stepy = -1;
		wall->sidedisty = (info->pos_y - wall->map_y) * wall->deldisty;
	}
	else
	{
		wall->stepy = 1;
		wall->sidedisty = (wall->map_y - info->pos_y + 1.0) * wall->deldisty;
	}
}

void	wall_dda(t_wall *wall, t_info *info)
{
	while (wall->hit == 0)
	{
		if (wall->sidedistx < wall->sidedisty)
		{
			wall->sidedistx += wall->deldistx;
			wall->map_x += wall->stepx;
			wall->side = 0;
		}
		else
		{
			wall->sidedisty += wall->deldisty;
			wall->map_y += wall->stepy;
			wall->side = 1;
		}
		if (info->worldmap[wall->map_x][wall->map_y] == 1)
			wall->hit = 1;
	}
}

void	wall_dist(t_wall *wall, t_info *info)
{
	if (wall->side == 0)
		wall->pwalldist = ((wall->map_x - info->pos_x)
				+ (1 - wall->stepx) / 2) / wall->raydir_x;
	else
		wall->pwalldist = ((wall->map_y - info->pos_y)
				+ (1 - wall->stepy) / 2) / wall->raydir_y;
	wall->lineh = (int)(info->height / wall->pwalldist);
	wall->dstart = (info->height - wall->lineh) / 2;
	if (wall->dstart < 0)
		wall->dstart = 0;
	wall->dend = (info->height + wall->lineh) / 2;
	if (wall->dend >= info->height)
		wall->dend = info->height - 1;
}

void	wall_texture(t_wall *wall, t_info *info)
{
	if (wall->side == 0)
	{
		if (wall->map_x > info->pos_x)
			wall->texnum = 3;
		else
			wall->texnum = 2;
	}
	else
	{
		if (wall->map_y > info->pos_y)
			wall->texnum = 0;
		else
			wall->texnum = 1;
	}
	if (wall->side == 0)
		wall->wallx = info->pos_y + wall->pwalldist * wall->raydir_y;
	else
		wall->wallx = info->pos_x + wall->pwalldist * wall->raydir_x;
	wall->wallx -= floor(wall->wallx);
	wall->tex_x = (int)(wall->wallx * (double)TEXWIDTH);
	if (wall->side == 0 && wall->raydir_x > 0)
		wall->tex_x = TEXWIDTH - wall->tex_x - 1;
	if (wall->side == 1 && wall->raydir_y < 0)
		wall->tex_x = TEXWIDTH - wall->tex_x - 1;
}
