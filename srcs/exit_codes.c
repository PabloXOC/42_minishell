/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_codes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:55:06 by ffauth-p          #+#    #+#             */
/*   Updated: 2024/07/01 17:02:16 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_and_control_c(int exit_code)
{
	if (exit_code == EXIT_128)
	{
		g_exit_status = EXIT_128;
		return (EXIT_128);
	}
	if (exit_code == EXIT_130)
	{
		g_exit_status = EXIT_130;
		return (EXIT_130);
	}
	return (SUCCESS);
}

int	exit_codes(int exit_code)
{
	if (exit_code == EXIT_1)
	{
		g_exit_status = EXIT_1;
		return (EXIT_1);
	}
	if (exit_code == EXIT_2)
	{
		g_exit_status = EXIT_2;
		return (EXIT_2);
	}
	if (exit_code == EXIT_126)
	{
		g_exit_status = EXIT_126;
		return (EXIT_126);
	}
	if (exit_code == EXIT_127)
	{
		g_exit_status = EXIT_127;
		return (EXIT_127);
	}
	return (exit_and_control_c(exit_code));
}
