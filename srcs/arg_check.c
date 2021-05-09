/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 13:58:24 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/08 14:36:29 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_check(char *s)
{
	int	len;

	len = ft_strlen(s);
	return (s[len - 4] == '.' && s[len - 3] == 'c' && s[len - 2] == 'u'
		&& s[len - 1] == 'b' && s[len] == '\0');
}

int	flag_check(char *s)
{
	return (s[0] == '-' && s[1] == '-' && s[2] == 's' && s[3] == 'a'
		&& s[4] == 'v' && s[5] == 'e' && s[6] == '\0');
}

int	arg_check(int argc, char **argv, t_file *file)
{
	file->bmp_flag = 0;
	if (argc < 2)
		printf("Error : no map file\n");
	else if (argc > 3)
		printf("Error : too many arguments\n");
	else if (!file_check(argv[1]))
		printf("Error : no vaild map file\n");
	else if (argc == 3 && !flag_check(argv[2]))
		printf("Error : invalid flag\n");
	else if (argc == 3)
	{
		file->bmp_flag = 1;
		file->filename = ft_strdup(argv[1]);
		return (1);
	}
	else
	{
		file->filename = ft_strdup(argv[1]);
		return (1);
	}
	return (-1);
}
