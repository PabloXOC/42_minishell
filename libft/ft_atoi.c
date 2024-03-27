/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:52:24 by pximenez          #+#    #+#             */
/*   Updated: 2024/02/14 17:04:28 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	loop;
	int	temp;

	temp = 0;
	loop = 0;
	sign = 1;
	while (str[loop] == 32)
		loop++;
	if (str[loop] == '+' || str[loop] == '-')
	{
		if (str[loop] == '-')
			sign = sign * -1;
		loop++;
	}
	while (str[loop] >= '0' && str[loop] <= '9')
	{
		temp = 10 * temp + str[loop] - '0';
		loop++;
	}
	return (temp * sign);
}

/* int	main(void)
{
	printf("%d\n", ft_atoi(" \n\t\f\v  +214483648"));
	printf("%d\n", atoi(" \n\t\f\v  +214748648"));
} */
