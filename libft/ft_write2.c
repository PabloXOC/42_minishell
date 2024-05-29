/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:01:28 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/12 14:25:32 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_xx(unsigned int nb, int len, char *hexa)
{
	if (nb > 15)
		len = ft_xx(nb / 16, len, hexa);
	write(1, &hexa[nb % 16], 1);
	len++;
	return (len);
}

int	ft_perc(int len)
{
	write(1, "%%", 1);
	return (len + 1);
}
