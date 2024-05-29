/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:46:58 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/04 11:27:37 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*b_ptr;

	b_ptr = (char *)b;
	i = 0;
	while (i < len)
		b_ptr[i++] = c;
	return (b);
}

/* int	main(void)
{
	char	dst[15] = "hola que tal";
	char	src[15] = "muy buenas";
	int 	i;

	i = 0;
	while (i < 15)
	{
		printf("SRCS: Character '%c' has ASCII value: %d\n", dst[i],
			(int)dst[i]);
		i++;
	}
	printf("\n");
	ft_memset(dst, 2, 4);
	i = 0;
	while (i < 15)
	{
		printf("SRCS: Character '%c' has ASCII value: %d\n", dst[i],
			(int)dst[i]);
		i++;
	}
} */
