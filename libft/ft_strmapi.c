/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:30:46 by pablo             #+#    #+#             */
/*   Updated: 2023/12/05 14:01:23 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* static	char	ft_f(unsigned int i, char c)
{
	i++;
	return (c + 1);
}
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		len;
	unsigned int		i;
	char				*s_new;

	len = ft_strlen(s);
	s_new = ft_calloc(len + 1, 1);
	if (s_new == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s_new[i] = f(i, s[i]);
		i++;
	}
	s_new[i] = 0;
	return (s_new);
}

/* int	main(void)
{
	printf("%s", ft_strmapi("hola que tal", &ft_f));
} */
