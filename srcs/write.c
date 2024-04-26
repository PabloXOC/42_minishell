/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:28:55 by paxoc01           #+#    #+#             */
/*   Updated: 2024/04/26 13:14:38 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write_error_i(t_cases case_code, t_command *command)
{
	if (case_code == MALLOC_ERROR)
	{
		printf("Memory allocation failed: %s\n", strerror(errno));
		return (MALLOC_ERROR);
	}
	if (case_code == INVALID_COMMAND)
	{
		ft_printf("Command '%s' not found.\n", command->command_parsed[0]);
		return (INVALID_COMMAND);
	}
	return (SUCCESS);
}

char	*ft_write_error_c(t_cases case_code, t_command *command)
{
	if (case_code == MALLOC_ERROR)
	{
		printf("Memory allocation failed: %s\n", strerror(errno));
		return (NULL);
	}
	if (case_code == INVALID_COMMAND)
	{
		ft_printf("Command '%s' not found.\n", command->command_parsed[0]);
		return (NULL);	
	}
	return (SUCCESS);
}