/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:26:58 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/06 11:40:33 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/* int	main(void)
{
	char	str1[18] = "hola ";
	char	str2[20] = "muybuenas";
	char	str3[18] = "hola ";
	char	str4[20] = "muybuenas";
	int		n;

	n = 0;
	printf("%lu  ", ft_strlcpy(str1, str2, n));
	printf("%s\n", str1);
	printf("%lu  ", strlcpy(str3, str4, n));
	printf("%s\n", str3);
} */
