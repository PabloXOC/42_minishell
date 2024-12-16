/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_codes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:55:06 by ffauth-p          #+#    #+#             */
/*   Updated: 2024/07/02 16:20:46 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_codes(int exit_code, t_data *data)
{
	g_exit_status = exit_code;
	if (data != NULL)
	{
		if (refresh_mysignal_var(data) == MALLOC_ERROR)
		{
			exit_code = EXIT_1;
			g_exit_status = exit_code;
		}
	}
	return (exit_code);
}

int	exit_codes_main(int exit_code, t_data *data)
{
	g_exit_status = exit_code;
	if (data != NULL)
	{
		if (refresh_mysignal_var(data) == MALLOC_ERROR)
		{
			exit_code = EXIT_1;
			g_exit_status = exit_code;
		}
	}
	total_cleanup(data);
	return (exit_code);
}
