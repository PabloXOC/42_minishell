/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:46:58 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/04 16:48:06 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	i;
	size_t	totalsize;

	totalsize = nmemb * size;
	if (nmemb != 0 && (totalsize / nmemb != size))
		return (NULL);
	str = (char *)malloc(nmemb * size);
	if (!(str))
		return (NULL);
	i = 0;
	while (i < nmemb * size)
		str[i++] = 0;
	return (str);
}

/* int	main(void)
{
	char	*src;
	int		i;
	void	*str;

	i = 0;
	while (i < 50)
	{
		printf("SRCS: Character '%d' has ASCII value: %d\n", i, (int)src[i]);
		i++;
	}
	printf("\n");
	src = (char *)ft_calloc(5, 5);
	printf("<<%s>>", src);
	i = 0;
	while (i < 50)
	{
		printf("SRCS: Character '%d' has ASCII value: %d\n", i, (int)src[i]);
		i++;
	}
	free(src);
} */
/* int	main(void)
{
	char *str = calloc(0, 0);

	printf("%d", (int) str[0]);
	if (str == ((void *)0))
	{
		printf("%s", (void *)0);
		write(1, "no", 2);
	}
	else
		write(1, "hi", 2);
	free(str);
} */
