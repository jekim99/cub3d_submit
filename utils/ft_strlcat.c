/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:05:55 by jaeekim           #+#    #+#             */
/*   Updated: 2021/04/25 16:06:17 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t result;
	size_t src_l;

	i = ft_strlen(dst);
	src_l = ft_strlen(src);
	if (size < i)
		return (src_l + size);
	result = i + src_l;
	while (*src && i + 1 < size)
	{
		dst[i] = *src;
		i++;
		src++;
	}
	dst[i] = '\0';
	return (result);
}
