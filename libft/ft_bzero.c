/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:46:58 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/04 11:27:48 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*s_ptr;

	s_ptr = (char *)s;
	i = 0;
	while (i < n)
		s_ptr[i++] = 0;
	return ;
}

/* int	main(void)
{
	char	str[12];
	int i;

	i = 0;
	while (i < 10)
	{
		printf("SRCS: Character '%c' has ASCII value: %d\n", str[i],
			(int)str[i]);
		i++;
	}
	printf("\n");
	ft_bzero(str, 7);
	i = 0;
	while (i < 10)
	{
		printf("SRCS: Character '%c' has ASCII value: %d\n", str[i],
			(int)str[i]);
		i++;
	}
} */
