/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:46:58 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/04 12:12:43 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] - s2[i] != 0)
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	if (s1[i] - s2[i] != 0 && i != n)
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	return (0);
}

/* int	main(void)
{
	char s1[15] = "hola que tal";
	char s2[15] = "hola que tal";

	printf("%d\n", strncmp(s1, s2, 16));
	printf("%d\n", ft_strncmp(s1, s2, 16));
} */

/* int main(void)
{
	char *s1 = "\200";
	char *s2 = "\0";
	int 	i;

	printf("SRCS: Character '%s' has ASCII value: %d\n", s1,
		(int)s1[i]);
	printf("SRCS: Character '%s' has ASCII value: %d\n", s2,
		(int)s2[i]);
	printf("%s\n", s1);
	printf("%s\n", s1);
	int i1 = strncmp(s1, s2, 1);
	int i2 = ft_strncmp(s1, s2, 1);
	printf("%d, %d\n", i1, i2);
} */
