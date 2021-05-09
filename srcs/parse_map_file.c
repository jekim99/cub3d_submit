/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:00:41 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 14:05:01 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	get_file(char *argv)
{
	t_cub	cub;
	int		fd;
	char	*line;
	int		result;

	cub = initialization_cub();
	result = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		error_parse_map(6);
	while (1)
	{
		result = get_next_line(fd, &line);
		if (result < 0)
			error_parse_map(7);
		check_configuration(line, &cub);
		free(line);
		if (result <= 0)
			break ;
	}
	close(fd);
	return (cub);
}

int		check_configuration(char *str, t_cub *cub)
{
	int		i;

	if (check_map_start(str) == 1)
		cub->map.mapstart = 1;
	if (cub->map.mapend == 1 && ft_strlen(str) != 0)
		return (error_parse_map(4));
	if (cub->map.mapstart == 1)
		return (save_map(str, cub));
	if (ft_strlen(str) == 0)
		return (1);
	i = check_identifier(str);
	if (i == -1)
		return (error_parse_map(1));
	else if (check_doup_conf(i, cub) == -1)
		return (error_parse_map(1));
	else
	{
		cub->save[cub->cnt] = i;
		cub->cnt++;
		parse_configuration(i, str, cub);
	}
	return (1);
}

int		check_identifier(char *str)
{
	if (str[0] == 'R' && ft_isspace(str[1]))
		return (I_R);
	else if (str[0] == 'N' && str[1] == 'O' && ft_isspace(str[2]))
		return (I_NO);
	else if (str[0] == 'S' && str[1] == 'O' && ft_isspace(str[2]))
		return (I_SO);
	else if (str[0] == 'W' && str[1] == 'E' && ft_isspace(str[2]))
		return (I_WE);
	else if (str[0] == 'E' && str[1] == 'A' && ft_isspace(str[2]))
		return (I_EA);
	else if (str[0] == 'S' && ft_isspace(str[1]))
		return (I_S);
	else if (str[0] == 'F' && ft_isspace(str[1]))
		return (I_F);
	else if (str[0] == 'C' && ft_isspace(str[1]))
		return (I_C);
	return (-1);
}
