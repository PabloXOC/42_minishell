/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:01:28 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/13 11:38:19 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_c(char c, int len)
{
	write(1, &c, 1);
	return (len + 1);
}

int	ft_s(char *s, int len)
{
	int		i;

	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (len + 6);
	}
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i + len);
}

int	ft_p(uintptr_t nb, int len, char *hexa)
{
	if (nb > 15)
		len = ft_p(nb / 16, len, hexa);
	write(1, &hexa[nb % 16], 1);
	len++;
	return (len);
}

int	ft_di(int nb, int len)
{
	char	rest;

	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (len + 11);
	}
	if (nb < 0)
	{
		nb = nb * -1;
		write(1, "-", 1);
		len++;
	}
	if (nb > 9)
		len = ft_di(nb / 10, len);
	rest = nb % 10 + 48;
	write(1, &rest, 1);
	len++;
	return (len);
}

int	ft_u(unsigned int nb, int len)
{
	unsigned int	rest;

	if (nb > 9)
		len = ft_u(nb / 10, len);
	rest = nb % 10 + 48;
	write(1, &rest, 1);
	len++;
	return (len);
}
