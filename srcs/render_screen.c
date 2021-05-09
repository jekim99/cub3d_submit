/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:19:00 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 14:10:32 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_screen(t_info *info)
{
	mlx_loop_hook(info->mlx, &render_main_loop, info);
}

void	render_draw(t_info *info)
{
	int	x;
	int	y;
	int	p;

	x = 0;
	y = 0;
	p = (info->img.size_l - info->width * (info->img.bpp / 8)) / 4;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			info->img.data[y * (info->width + p) + x] = info->buff[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int		render_main_loop(t_info *info)
{
	render_calc(info);
	render_draw(info);
	return (0);
}

void	render_calc(t_info *info)
{
	floor_casting(info);
	wall_casting(info);
	sprite_casting(info);
}
