/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/07/03 13:38:02 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_var(t_data *data, char *var_to_del, t_var **list)
{
	t_var	*vars;
	t_var	*temp_var;

	vars = *list;
	if (vars == NULL)
		return (SUCCESS);
	if (vars != NULL)
	{
		if (ft_strncmp(vars->var, var_to_del, ft_strlen(var_to_del)) == 0)
			return (delete_head_var(vars, temp_var, list));
	}
	while (vars->next != NULL)
	{
		if (ft_strncmp(vars->next->var, var_to_del, ft_strlen(var_to_del)) == 0)
			return (delete_middle_var(vars, temp_var));
		vars = vars->next;
	}
	return (SUCCESS);
}

int	refresh_mysignal_var(t_data *data)
{
	char	**equality;

	equality = (char **)malloc(3 * sizeof(char *));
	if (equality == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	equality[2] = NULL;
	equality[0] = ft_strdup("?");
	equality[1] = ft_itoa(g_exit_status);
	if (equality[0] == NULL || equality[1] == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	save_var_info(data, equality, &data->var);
	return (SUCCESS);
}
