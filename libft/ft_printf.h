/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:01:07 by pablo             #+#    #+#             */
/*   Updated: 2024/01/25 18:25:53 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//libft
# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
//printf
# include <stdarg.h>
# include <stdint.h>

//funciones
int	ft_printf(char const *fmt, ...);
int	ft_c(char c, int len);
int	ft_s(char *s, int len);
int	ft_p(uintptr_t nb, int len, char *hexa);
int	ft_di(int nb, int len);
int	ft_u(unsigned int nb, int len);
int	ft_xx(unsigned int nb, int len, char *hexa);
int	ft_perc(int len);

#endif
