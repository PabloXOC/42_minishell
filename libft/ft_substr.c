/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:46:58 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/06 13:23:24 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		subs = ft_calloc(1, 1);
		if (subs == NULL)
			return (NULL);
		return (subs);
	}
	if (s_len - start >= len)
		subs = ft_calloc(len + 1, 1);
	else
		subs = ft_calloc(s_len - start + 1, 1);
	if (subs == NULL)
		return (NULL);
	if (s_len - start >= len)
		ft_strlcpy(subs, &s[start], len + 1);
	else
		ft_strlcpy(subs, &s[start], len);
	return (subs);
}

/* int	main(void)
{
	char	*dst;
	int		i;

	char *src = "hola";
	dst = ft_substr(src, 0, 18446744073709551615);
	printf("<%s>\n", dst);
} */

/* int main(void)
{
	char *str = "01234";
	size_t size = 10;
	char *ret = ft_substr(str, 10, size);

	if (!strncmp(ret, "", 1))
	{
		write(1, "yes\n", 4);
	}
	write(1, "no\n", 3);
} */
