/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:46:58 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/06 13:41:02 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	while (ft_strchr(set, s1[i]) != NULL && i < ft_strlen(s1))
		i++;
	if (ft_strlen(s1) == i)
	{
		str = (char *)malloc(1 * 1);
		if (!(str))
			return (NULL);
		str[0] = 0;
		return (str);
	}
	j = 0;
	while (ft_strchr(set, s1[ft_strlen(s1) - j - 1]) != NULL)
		j++;
	str = ft_calloc(ft_strlen(s1) - i - j + 1, 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, &s1[i], ft_strlen(s1) - i - j);
	str[ft_strlen(s1) - i - j] = 0;
	return (str);
}

/* int	main(void)
{
	char	s1[40] = "  a a haaolaquaaetaal fdf  aa ";
	char	set[20] = " afd";
	char	*dst;

	dst = ft_strtrim("", "");
	printf("%s\n", dst);
	free(dst);
} */
