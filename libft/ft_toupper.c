/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:46:58 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/01 12:51:35 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ((c >= 97 && c <= 122))
		return (c - (97 - 65));
	else
		return (c);
}

/* int	main(void)
{
	printf("%d\n", toupper(100));
	printf("%d\n\n", ft_toupper(100));
	printf("%d\n", toupper(50));
	printf("%d\n", ft_toupper(50));
} */
