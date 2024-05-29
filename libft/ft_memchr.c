/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:47:19 by pablo             #+#    #+#             */
/*   Updated: 2023/12/06 12:18:56 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*chr_s;
	size_t			i;

	i = 0;
	chr_s = (unsigned char *)s;
	while (i < n)
	{
		if (chr_s[i] == (unsigned char)c)
			return (&chr_s[i]);
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	int		i;
	char *src = "/|\x12\xff\x09\x42\2002\42|\\";
    int size = 10;
	char	*hi;

	i = 0;
	while (i < 12)
	{
		printf("DEST: Character '%c' has ASCII value: %d\n", src[i],
			(int)src[i]);
		i++;
	}
	hi = (char *) memchr(src, 0, 20);
	printf("\n");
	i = 0;
	while (i < 10)
	{
		printf("DEST: Character '%c' has ASCII value: %d\n", hi[i],
			(int)hi[i]);
		i++;
	}
} */
