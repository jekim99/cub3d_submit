/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_interaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:28:10 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 13:46:11 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_interaction(t_info *info)
{
	mlx_hook(info->win, KEY_PRESS, 0, &key_press, info);
	mlx_hook(info->win, KEY_RELEASE, 0, &key_release, info);
	mlx_hook(info->win, DESTROY_NOTIFY, 0, &button_click, info);
}

int		key_release(int key)
{
	if (key == K_ESC)
		exit(0);
	return (0);
}

int		button_click(void)
{
	exit(0);
	return (0);
}
