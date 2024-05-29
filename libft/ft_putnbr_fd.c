/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:09:05 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/05 14:21:44 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_recursive_write(int nb, int fd)
{
	int	rest;

	if (nb > 9)
	{
		ft_recursive_write(nb / 10, fd);
	}
	rest = nb % 10;
	rest = rest + 48;
	write(fd, &rest, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		nb = nb * -1;
		write(fd, "-", 1);
	}
	ft_recursive_write(nb, fd);
}

/* int	main(void)
{
	int	var;

	var = -2147483648;
	ft_putnbr(var);
} */
