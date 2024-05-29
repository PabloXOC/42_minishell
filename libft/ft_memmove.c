/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:58:46 by pablo             #+#    #+#             */
/*   Updated: 2023/12/04 11:58:53 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*chr_dst;
	char	*chr_src;
	size_t	i;

	chr_dst = (char *)dest;
	chr_src = (char *)src;
	if (chr_dst == NULL && chr_src == NULL)
		return (NULL);
	i = 0;
	if (chr_dst < chr_src || chr_dst >= chr_src + n)
	{
		while (i < n)
		{
			chr_dst[i] = chr_src[i];
			i++;
		}
		return (chr_dst);
	}
	while (i < n)
	{
		chr_dst[n - i - 1] = chr_src[n - i - 1];
		i++;
	}
	return (chr_dst);
}

/* int	main(void)
{
	int		i;
	char	src[12] = "ABCDEFGHIJ";
	char	dst[12] = "0123456789";

	i = 0;
	while (i < 12)
	{
		printf("SRCS: Character '%c' has ASCII value: %d\n", src[i],
			(int)src[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < 12)
	{
		printf("DEST: Character '%c' has ASCII value: %d\n", dst[i],
			(int)dst[i]);
		i++;
	}
	ft_memmove(dst, dst + 2, 3);
	printf("\n");
	i = 0;
	while (i < 12)
	{
		printf("SRCS: Character '%c' has ASCII value: %d\n", src[i],
			(int)src[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < 12)
	{
		printf("DEST: Character '%c' has ASCII value: %d\n", dst[i],
			(int)dst[i]);
		i++;
	}
} */
