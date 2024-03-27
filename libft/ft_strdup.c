/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:46:58 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/01 16:27:59 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*output;

	len = ft_strlen(s);
	output = (char *)malloc((len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		output[i] = s[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

/* int	main(void)
{
	char	src[] = "holaquetal";
	char	*dest;

	dest = ft_strdup(src);
	printf("%s\n", dest);
} */
