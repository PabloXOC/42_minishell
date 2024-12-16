/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:30:46 by pablo             #+#    #+#             */
/*   Updated: 2023/12/05 13:56:21 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* static	char	ft_f(unsigned int i, char c)
{
	i++;
	return (c + 1);
} */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int		len;
	unsigned int		i;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}

/* int	main(void)
{
	printf("%s", ft_strmapi("hola que tal", &ft_f));
} */
