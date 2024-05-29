/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:09:05 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/06 11:26:03 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_numlen(int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		if (nb == -2147483648)
			nb = nb + 2;
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static	char	*ft_middle(char *str, int neg, int i, int nb)
{
	int	len;

	len = ft_numlen(nb);
	if (nb < 0)
	{
		str[i] = '-';
		nb = nb * -1;
		neg = 1;
	}
	while (i + neg < len)
	{
		str[len - i - 1] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	str[len] = 0;
	return (str);
}

static	char	*ft_long_num(char *str)
{
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = 0;
	return (str);
}

char	*ft_itoa(int nb)
{
	int		neg;
	char	*str;

	str = ft_calloc(ft_numlen(nb) + 1, 1);
	if (str == NULL)
		return (NULL);
	neg = 0;
	if (nb == -2147483648)
	{
		str = ft_long_num(str);
		return (str);
	}
	if (nb == 0)
	{
		str[0] = '0';
		str[1] = 0;
		return (str);
	}
	ft_middle(str, neg, 0, nb);
	return (str);
}

/* int	main(void)
{
	int		var;

	var = 10;
	printf("%s\n", ft_itoa(var));
} */
