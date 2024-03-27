/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:46:58 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/06 11:38:30 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_ptr;
	char	*src_ptr;

	dst_ptr = (char *)dst;
	src_ptr = (char *)src;
	if (dst_ptr == NULL && src_ptr == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dst_ptr[i] = src_ptr[i];
		i++;
	}
	return (dst);
}

/* int	main(void)
{
	char	*dst;
	char	*src;
	int		i;

	i = 0;
	while (i < 10)
	{
		printf("SRCS: Character '%c' has ASCII value: %d\n", dst[i],
			(int)dst[i]);
		i++;
	}
	printf("\n");
	dst = (char *)memcpy(NULL, "hi", 2);
	printf("%s", dst);
	i = 0;
	while (i < 10)
	{
		printf("SRCS: Character '%c' has ASCII value: %d\n", dst[i],
			(int)dst[i]);
		i++;
	}
} */
