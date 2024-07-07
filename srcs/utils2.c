/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:53:03 by paxoc01           #+#    #+#             */
/*   Updated: 2024/07/06 15:27:27 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_char_pp(char **stack)
{
	int	i;

	i = 0;
	while (stack[i] != NULL && stack[i] != "")
	{
		free(stack[i]);
		i++;
	}
	free (stack);
}

bool	ft_quote_switch(char *str, int i, bool single_q, bool double_q)
{
	if (str[i] == '\'' && single_q == false)
		return (true);
	else if (str[i] == '\'' && single_q == true)
		return (false);
	else if (str[i] == '\"' && double_q == false)
		return (true);
	else if (str[i] == '\"' && double_q == true)
		return (false);
	return (false);
}

int	ft_control_d(t_data *data)
{
	data->exit = true;
	return (CONTROL_D);
}
