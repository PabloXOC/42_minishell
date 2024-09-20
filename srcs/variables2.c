/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/09/20 16:44:15 by paxoc01          ###   ########.fr       */
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
	{
		ft_free_char_pp(equality);
		return (ft_write_error_i(MALLOC_ERROR, data));
	}
	save_var_info(data, equality, &data->var);
	return (SUCCESS);
}

int	refresh_home_var(t_data *data)
{
	char	**equality;

	if (return_content_var(data->env_lst, "HOME") == NULL)
		return (SUCCESS);
	equality = (char **)malloc(3 * sizeof(char *));
	if (equality == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	equality[2] = NULL;
	equality[0] = ft_strdup("~");
	equality[1] = ft_strdup(return_content_var(data->env_lst, "HOME"));
	if (equality[0] == NULL || equality[1] == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	save_var_info(data, equality, &data->var);
	return (SUCCESS);
}

int	create_preset_vars(t_data *data)
{
	if (refresh_mysignal_var(data) != SUCCESS)
		return (MALLOC_ERROR);
	if (refresh_home_var(data) != SUCCESS)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

void	modify_exp_and_env(t_data *data, char *var, char *new_cont)
{
	t_var	*node;

	node = data->var_export;
	while (node != NULL)
	{
		if (ft_strncmp(var, node->var, ft_strlen(var) + 1) == 0)
		{
			free(node->content);
			node->content = ft_strdup(new_cont);
		}
		node = node->next;
	}
	node = data->env_lst;
	while (node != NULL)
	{
		if (ft_strncmp(var, node->var, ft_strlen(var) + 1) == 0)
		{
			free(node->content);
			node->content = ft_strdup(new_cont);
		}
		node = node->next;
	}
	return ;
}
