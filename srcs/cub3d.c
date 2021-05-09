/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:28:57 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 03:05:42 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_file	file;
	t_info	info;

	if (arg_check(argc, argv, &file) == -1)
		return (0);
	file.cub = get_file(file.filename);
	free(file.filename);
	set_game(&file.cub, &info);
	if (file.bmp_flag == 1)
		save_bitmap(&info);
	else
	{
		render_screen(&info);
		game_interaction(&info);
		mlx_loop(info.mlx);
	}
	return (0);
}
