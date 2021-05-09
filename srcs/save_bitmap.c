/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:26:16 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 14:11:12 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		save_bitmap(t_info *info)
{
	int				fd;
	int				p;

	fd = open("save.bmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		printf("Error : bitmap save failed\n");
		exit(0);
	}
	p = (4 - ((info->width * 3) % 4)) % 4;
	render_calc(info);
	save_bitmap_header(info, fd, p);
	save_bitmap_data(info, fd, p);
	close(fd);
	return (0);
}

void	bitmap_int_shift(unsigned char *s, int value)
{
	s[0] = (unsigned char)value;
	s[1] = (unsigned char)(value >> 8);
	s[2] = (unsigned char)(value >> 16);
	s[3] = (unsigned char)(value >> 24);
}

void	save_bitmap_header(t_info *info, int fd, int p)
{
	unsigned char	buff[54];
	int				size;

	ft_bzero(buff, 54);
	size = 54 + ((info->width * 3 + p) * info->height);
	buff[0] = (unsigned char)'B';
	buff[1] = (unsigned char)'M';
	bitmap_int_shift(buff + 2, size);
	buff[10] = 54;
	buff[14] = 40;
	bitmap_int_shift(buff + 18, info->width);
	bitmap_int_shift(buff + 22, info->height);
	buff[26] = 1;
	buff[28] = 24;
	write(fd, buff, 54);
}

void	save_bitmap_data(t_info *info, int fd, int p)
{
	unsigned char	zero[3];
	int				i;
	int				j;

	ft_bzero(zero, 3);
	i = info->height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < info->width)
		{
			write(fd, &info->buff[i][j], 3);
			j++;
		}
		write(fd, zero, p);
		i--;
	}
}
