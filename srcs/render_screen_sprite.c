/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen_sprite.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:24:52 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 03:36:58 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(t_spi *spi, int numsprite)
{
	int		i;
	int		j;
	int		idx;
	t_spi	tmp;

	i = 0;
	while (i < numsprite - 1)
	{
		idx = i;
		j = i + 1;
		while (j < numsprite)
		{
			if (spi[idx].spritedist < spi[j].spritedist)
			{
				tmp = spi[idx];
				spi[idx] = spi[j];
				spi[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	sprite_calc(t_sprite *sp, t_info *info, int i)
{
	sp->sp_x = info->spi[i].x - info->pos_x;
	sp->sp_y = info->spi[i].y - info->pos_y;
	sp->invdet = 1.0 / (info->plane_x * info->dir_y
			- info->plane_y * info->dir_x);
	sp->trx = sp->invdet * (info->dir_y * sp->sp_x - info->dir_x * sp->sp_y);
	sp->try = sp->invdet * (-info->plane_y * sp->sp_x
			+ info->plane_x * sp->sp_y);
	sp->spritescreenx = (int)((info->width / 2) * (1 + sp->trx / sp->try));
	sp->sph = (int)fabs(info->height / sp->try);
	sp->drawstarty = (info->height - sp->sph) / 2;
	if (sp->drawstarty < 0)
		sp->drawstarty = 0;
	sp->drawendy = (info->height + sp->sph) / 2;
	if (sp->drawendy >= info->height)
		sp->drawendy = info->height - 1;
	sp->spw = (int)fabs(info->height / sp->try);
	sp->drawstartx = sp->spritescreenx - sp->spw / 2;
	if (sp->drawstartx < 0)
		sp->drawstartx = 0;
	sp->drawendx = sp->spritescreenx + sp->spw / 2;
	if (sp->drawendx >= info->width)
		sp->drawendx = info->width - 1;
}

void	sprite_vert_loop(t_sprite *sp, t_info *info)
{
	int		stripe;
	int		y;
	int		color;
	int		d;

	stripe = sp->drawstartx - 1;
	while (++stripe < sp->drawendx)
	{
		sp->tex_x = (int)((256 * (stripe - (sp->spritescreenx - sp->spw / 2))
					* TEXWIDTH / sp->spw) / 256);
		if (sp->try > 0 && stripe > 0 && stripe < info->width
			&& sp->try < info->zbuff[stripe])
		{
			y = sp->drawstarty - 1;
			while (++y < sp->drawendy)
			{
				d = y * 256 - info->height * 128 + sp->sph * 128;
				sp->tex_y = (d * TEXHEIGHT / sp->sph) / 256;
				color = info->texture[4][TEXWIDTH * sp->tex_y + sp->tex_x];
				if ((color & 0x00FFFFFF) != 0)
					info->buff[y][stripe] = color;
			}
		}
	}
}

void	sprite_casting(t_info *info)
{
	t_sprite	sp;
	int			i;

	i = 0;
	while (i < info->numsprite)
	{
		info->spi[i].spritedist = pow((info->pos_x - info->spi[i].x), 2)
			+ pow((info->pos_y - info->spi[i].y), 2);
		i++;
	}
	sort_sprites(info->spi, info->numsprite);
	i = 0;
	while (i < info->numsprite)
	{
		sprite_calc(&sp, info, i);
		sprite_vert_loop(&sp, info);
		i++;
	}
}
