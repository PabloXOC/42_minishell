/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/09/21 14:32:17 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_existing_var(t_var **list, char **equality, t_data *data)
{
	t_var	*temp_var;

	temp_var = *list;
	while (temp_var != NULL)
	{
		if (strncmp(temp_var->var, equality[0], ft_strlen(equality[0])) == 0)
		{
			free(temp_var->content);
			temp_var->content = ft_strdup(equality[1]);
			ft_free_char_pp(equality);
			if (temp_var->content == NULL)
				return (error_i(MALLOC_ERROR, data));
			return (SUCCESS);
		}
		temp_var = temp_var->next;
	}
	return (FAILURE);
}
