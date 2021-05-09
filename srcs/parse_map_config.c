/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:03:06 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 14:04:36 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_configuration(int i, char *str, t_cub *cub)
{
	if (i == I_R)
		r_to_resolution(str + 2, cub);
	else if (i == I_NO)
		cub->texture[0] = tex_to_path(str + 3);
	else if (i == I_SO)
		cub->texture[1] = tex_to_path(str + 3);
	else if (i == I_WE)
		cub->texture[2] = tex_to_path(str + 3);
	else if (i == I_EA)
		cub->texture[3] = tex_to_path(str + 3);
	else if (i == I_S)
		cub->texture[4] = tex_to_path(str + 2);
	else if (i == I_F)
		cub->floor = rgb_to_hex(str + 2);
	else if (i == I_C)
		cub->ceiling = rgb_to_hex(str + 2);
	return (1);
}

int		r_to_resolution(char *str, t_cub *cub)
{
	int		i;

	i = 0;
	skip_space(str, &i);
	while (ft_isdigit(str[i]))
		cub->screenwidth = cub->screenwidth * 10 + str[i++] - '0';
	skip_space(str, &i);
	while (ft_isdigit(str[i]))
		cub->screenheight = cub->screenheight * 10 + str[i++] - '0';
	if ((check_str_remain(str + i) == -1) || cub->screenheight == 0
		|| cub->screenwidth == 0)
		return (error_parse_map(2));
	return (1);
}

char	*tex_to_path(char *str)
{
	char	*path;
	int		i;

	i = 0;
	skip_space(str, &i);
	if (ft_strlen(str + i) == 0)
		error_parse_map(5);
	path = ft_strdup(str + i);
	return (path);
}

int		rgb_calc(char *split)
{
	int		j;
	int		value;

	value = 0;
	j = 0;
	skip_space(split, &j);
	while (ft_isdigit(split[j]))
		value = value * 10 + split[j++] - '0';
	if ((value > 255 || value < 0) || check_str_remain(split + j) == -1)
		return (error_parse_map(3));
	return (value);
}

int		rgb_to_hex(char *str)
{
	int		i;
	char	**split;
	int		color[3];
	int		color_hex;

	color_hex = 0;
	i = 0;
	if (!check_split(str, ','))
		return (error_parse_map(3));
	split = ft_split(str, ',');
	while (i < 3)
	{
		if (!split[i])
		{
			free(split);
			return (error_parse_map(3));
		}
		color[i] = rgb_calc(split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	color_hex = (color[0] << 16) + (color[1] << 8) + color[2];
	return (color_hex);
}
