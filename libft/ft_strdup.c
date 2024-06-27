/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:46:58 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/27 17:37:02 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*output;

	if (s == NULL)
		return (NULL);
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
