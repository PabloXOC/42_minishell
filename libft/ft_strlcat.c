/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:51:04 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/06 11:40:38 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	loop;
	size_t	size_src;
	size_t	size_dest;

	size_src = ft_strlen(src);
	size_dest = ft_strlen(dst);
	loop = 0;
	if (dstsize > size_dest)
	{
		while (src[loop] != 0 && (dstsize - loop - 1 > size_dest))
		{
			dst[loop + size_dest] = src[loop];
			loop++;
		}
		dst[loop + size_dest] = '\0';
		return (size_dest + size_src);
	}
	return (dstsize + size_src);
}

/* int	main(void)
{
	char	str1[18] = "hola ";
	char	str2[20] = "muybuenas";
	char	str3[18] = "hola ";
	char	str4[20] = "muybuenas";
	int		n;

	n = 18;
	printf("%lu  ", ft_strlcat(str1, str2, n));
	printf("%s\n", str1);
	printf("%lu  ", strlcat(str3, str4, n));
	printf("%s\n", str3);
} */
