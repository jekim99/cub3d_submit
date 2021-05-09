/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_interaction_key.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:27:41 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 13:43:50 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int key, t_info *info)
{
	if (key == K_W || key == K_S)
		key_press_ws(key, info);
	if (key == K_A || key == K_D)
		key_press_ad(key, info);
	if (key == K_AR_L || key == K_AR_R)
		key_press_rotate(key, info);
	if (key == K_ESC)
		exit(0);
	return (0);
}

void	key_press_ws(int key, t_info *info)
{
	if (key == K_W)
	{
		if (info->worldmap[(int)(info->pos_x + info->dir_x * info->movespeed)]
			[(int)info->pos_y] != 1)
			info->pos_x += info->dir_x * info->movespeed;
		if (info->worldmap[(int)info->pos_x]
			[(int)(info->pos_y + info->dir_y * info->movespeed)] != 1)
			info->pos_y += info->dir_y * info->movespeed;
	}
	else
	{
		if (info->worldmap[(int)(info->pos_x - info->dir_x * info->movespeed)]
			[(int)info->pos_y] != 1)
			info->pos_x -= info->dir_x * info->movespeed;
		if (info->worldmap[(int)info->pos_x]
			[(int)(info->pos_y - info->dir_y * info->movespeed)] != 1)
			info->pos_y -= info->dir_y * info->movespeed;
	}
}

void	key_press_ad(int key, t_info *info)
{
	if (key == K_A)
	{
		if (info->worldmap[(int)info->pos_x]
			[(int)(info->pos_y + info->dir_x * info->movespeed)] != 1)
			info->pos_y += info->dir_x * info->movespeed;
		if (info->worldmap[(int)(info->pos_x - info->dir_y * info->movespeed)]
			[(int)info->pos_y] != 1)
			info->pos_x -= info->dir_y * info->movespeed;
	}
	else
	{
		if (info->worldmap[(int)info->pos_x]
			[(int)(info->pos_y - info->dir_x * info->movespeed)] != 1)
			info->pos_y -= info->dir_x * info->movespeed;
		if (info->worldmap[(int)(info->pos_x + info->dir_y * info->movespeed)]
			[(int)info->pos_y] != 1)
			info->pos_x += info->dir_y * info->movespeed;
	}
}

void	key_press_rotate(int key, t_info *info)
{
	double	old_dirx;
	double	old_planex;
	double	dir;

	if (key == K_AR_L)
		dir = 1.0;
	else
		dir = -1.0;
	old_dirx = info->dir_x;
	info->dir_x = info->dir_x * cos(dir * info->rotspeed)
		- info->dir_y * sin(dir * info->rotspeed);
	info->dir_y = old_dirx * sin(dir * info->rotspeed)
		+ info->dir_y * cos(dir * info->rotspeed);
	old_planex = info->plane_x;
	info->plane_x = info->plane_x * cos(dir * info->rotspeed)
		- info->plane_y * sin(dir * info->rotspeed);
	info->plane_y = old_planex * sin(dir * info->rotspeed)
		+ info->plane_y * cos(dir * info->rotspeed);
}
