/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:01:28 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/13 13:00:51 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_type(int type_c, int len, va_list va_str)
{
	if (type_c == 1)
		len = ft_c(va_arg(va_str, int), len);
	if (type_c == 2)
		len = ft_s(va_arg(va_str, char *), len);
	if (type_c == 3)
	{
		len += write(1, "0x", 2);
		len = ft_p((uintptr_t)va_arg(va_str, void *), len, "0123456789abcdef");
	}
	if (type_c == 4)
		len = ft_di(va_arg(va_str, int), len);
	if (type_c == 5)
		len = ft_u(va_arg(va_str, unsigned int), len);
	if (type_c == 6)
		len = ft_xx(va_arg(va_str, unsigned int), len, "0123456789abcdef");
	if (type_c == 7)
		len = ft_xx(va_arg(va_str, unsigned int), len, "0123456789ABCDEF");
	if (type_c == 8)
		len = ft_perc(len);
	return (len);
}

static int	ft_check_fmt(char c)
{
	if (c == 'c')
		return (1);
	if (c == 's')
		return (2);
	if (c == 'p')
		return (3);
	if (c == 'd' || c == 'i')
		return (4);
	if (c == 'u')
		return (5);
	if (c == 'x')
		return (6);
	if (c == 'X')
		return (7);
	if (c == '%')
		return (8);
	if (c == 0)
		return (0);
	return (-1);
}

int	ft_printf(char const *fmt, ...)
{
	va_list	va_str;
	int		i;
	int		len;

	len = 0;
	i = 0;
	va_start(va_str, fmt);
	while (fmt[i] != 0)
	{
		if (fmt[i] == '%' && ft_check_fmt(fmt[i + 1]) == 0)
			return (len);
		else if (fmt[i] == '%')
		{
			if (ft_check_fmt(fmt[i + 1]) > 0)
				len = ft_print_type(ft_check_fmt(fmt[i++ + 1]), len, va_str);
		}
		else if (fmt[i] != '%' || ft_check_fmt(fmt[i + 1]) < 0)
		{
			write(1, &fmt[i], 1);
			len++;
		}
		i++;
	}
	va_end(va_str);
	return (len);
}

/* int	main(void)
{
	int		ret;
	int		i;
	void	*p;

	p = &i;
	ret = ft_printf("hola%s%p","hola", p);
	printf("%d\n", ret);
	printf("\n");
	ret = printf("<<%q>>");
	printf("%d\n", ret);
} */
