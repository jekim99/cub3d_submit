/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:41:49 by jaeekim           #+#    #+#             */
/*   Updated: 2021/04/25 16:10:54 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		array_1st(char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
			j++;
		i++;
	}
	if (s[j - 1] == c)
		i--;
	return (i);
}

static char		*ft_2nd_malloc(int i, int j)
{
	char *result;

	if (i == 0)
	{
		if (!(result = malloc(sizeof(char) * (j + 1))))
			return (NULL);
	}
	else if (!(result = malloc(sizeof(char) * (j - i + 1))))
		return (NULL);
	return (result);
}

static char		*array_assign_2nd(char const *s, char c, int *i)
{
	int		j;
	int		n;
	char	*result;

	j = *i;
	while (s[j++] == c)
		*i = *i + 1;
	while (j <= (int)ft_strlen(s))
	{
		if (s[j] == c || s[j] == '\0')
		{
			if (!(result = ft_2nd_malloc(*i, j)))
				return (NULL);
			n = -1;
			while ((*i + (++n)) < j)
				result[n] = s[*i + n];
			result[n] = '\0';
			while (s[j] == c)
				j++;
			*i = j;
			return (result);
		}
		j++;
	}
	return (NULL);
}

static void		freeall(char **result, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		free(result[j]);
		j++;
	}
	free(result);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		i_2nd;

	i = 0;
	i_2nd = 0;
	if (!(result = (char**)malloc(sizeof(char*) * (array_1st(s, c) + 1))))
		return (NULL);
	while (i < array_1st(s, c))
	{
		if (!(result[i] = array_assign_2nd(s, c, &i_2nd)))
		{
			freeall(result, i);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
