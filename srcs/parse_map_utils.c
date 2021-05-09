/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:06:21 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 14:05:26 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	initialization_map(void)
{
	t_map	map;

	map.mapstart = 0;
	map.mapend = 0;
	map.maprowmax = 0;
	map.mapcol = 0;
	map.mapsave = ft_strdup("");
	return (map);
}

t_cub	initialization_cub(void)
{
	t_cub	cub;

	cub.screenwidth = 0;
	cub.screenheight = 0;
	cub.floor = 0;
	cub.ceiling = 0;
	cub.cnt = 0;
	cub.map = initialization_map();
	return (cub);
}

void	skip_space(char *str, int *i)
{
	while (ft_isspace(str[*i]))
		(*i)++;
}

int		error_parse_map(int i)
{
	if (i == 1)
		printf("Error : invalid configuration\n");
	else if (i == 2)
		printf("Error : invalid resolution\n");
	else if (i == 3)
		printf("Error : invalid RGB value\n");
	else if (i == 4)
		printf("Error : invalid map\n");
	else if (i == 5)
		printf("Error : invalid path\n");
	else if (i == 6)
		printf("Error : invalid description file\n");
	else if (i == 7)
		printf("Error : no valid map file\n");
	exit(0);
}
