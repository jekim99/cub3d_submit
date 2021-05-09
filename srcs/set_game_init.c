/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:11:32 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 14:13:43 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_game(t_cub *cub, t_info *info)
{
	info_initialization(cub, info);
	info->worldmap = make_map(cub->map, info);
	free(cub->map.mapsave);
	if (map_valid_check(cub->map, info) != 1)
		error_parse_map(4);
	info->spi = make_sprite_info(cub->map, info);
}

void	load_texture(t_info *info, int *texture, char *path, t_img *img)
{
	int		x;
	int		y;
	int		p;

	img->img = mlx_xpm_file_to_image(info->mlx, path,
			&(img->img_width), &(img->img_height));
	if (!img->img)
		error_parse_map(5);
	img->data = (int *)mlx_get_data_addr(img->img, &(img->bpp),
			&(img->size_l), &(img->endian));
	y = 0;
	p = (img->size_l - img->img_width * (img->bpp / 8)) / 4;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[(img->img_width + p)
				* y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture_array(t_cub *cub, t_info *info)
{
	t_img	img;
	int		i;

	i = 0;
	while (i < 5)
	{
		load_texture(info, info->texture[i], cub->texture[i], &img);
		free(cub->texture[i]);
		i++;
	}
}

void	info_initialization_const(t_cub *cub, t_info *info)
{
	int		sizex;
	int		sizey;

	info->pos_x = 0;
	info->pos_y = 0;
	info->dir_x = 0;
	info->dir_y = 0;
	info->movespeed = 0.3;
	info->rotspeed = 0.2;
	info->mlx = mlx_init();
	mlx_get_screen_size(info->mlx, &sizex, &sizey);
	if (cub->screenwidth > sizex)
		info->width = sizex;
	else
		info->width = cub->screenwidth;
	if (cub->screenheight > sizey)
		info->height = sizey;
	else
		info->height = cub->screenheight;
	info->color[0] = cub->ceiling;
	info->color[1] = cub->floor;
}

void	info_initialization(t_cub *cub, t_info *info)
{
	int	i;
	int	j;

	i = 0;
	info_initialization_const(cub, info);
	info->buff = (int **)malloc(sizeof(int *) * info->height);
	while (i < info->height)
	{
		j = 0;
		(info->buff)[i] = (int *)malloc(sizeof(int) * info->width);
		while (j < info->width)
		{
			info->buff[i][j] = 0;
			j++;
		}
		i++;
	}
	info->numsprite = 0;
	info->zbuff = (double *)malloc(sizeof(double) * info->width);
	info->win = mlx_new_window(info->mlx, info->width, info->height, "cub3D");
	load_texture_array(cub, info);
	info->img.img = mlx_new_image(info->mlx, info->width, info->height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &(info->img.bpp),
			&(info->img.size_l), &(info->img.endian));
}
