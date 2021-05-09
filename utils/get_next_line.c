/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:43:28 by jaeekim           #+#    #+#             */
/*   Updated: 2021/04/25 16:09:33 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_new_line(char *backup)
{
	int			i;

	i = 0;
	while (backup[i])
	{
		if (backup[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	enc_new_line(char **backup, char **line, int index)
{
	char		*tmp;

	(*backup)[index] = '\0';
	*line = ft_strdup(*backup);
	if (ft_strlen(*backup + index + 1) == 0)
	{
		free(*backup);
		*backup = NULL;
		return (1);
	}
	tmp = ft_strdup(*backup + index + 1);
	free(*backup);
	*backup = tmp;
	return (1);
}

int	enc_eof(char **backup, char **line, int size)
{
	int			index;

	if (size < 0)
	{
		free(*backup);
		*backup = NULL;
		return (-1);
	}
	if (!(*backup))
	{
		free(*backup);
		*backup = NULL;
		*line = ft_strdup("");
		return (0);
	}
	else if ((index = find_new_line(*backup)) >= 0)
		return (enc_new_line(backup, line, index));
	else
		*line = ft_strdup(*backup);
	free(*backup);
	*backup = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char *backup[OPEN_MAX];
	char		buff[BUFFER_SIZE + 1];
	int			size;
	int			index;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[size] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buff);
		index = find_new_line(backup[fd]);
		if (index >= 0)
			return (enc_new_line(&backup[fd], line, index));
	}
	return (enc_eof(&backup[fd], line, size));
}
