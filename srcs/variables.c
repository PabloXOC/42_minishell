/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/09/16 16:27:18 by paxoc01          ###   ########.fr       */
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
				return (ft_write_error_i(MALLOC_ERROR, data));
			return (SUCCESS);
		}
		temp_var = temp_var->next;
	}
	return (FAILURE);
}

int	save_var_info(t_data *data, char **equality, t_var **list)
{
	t_var	*temp_var;

	if (*list != NULL)
	{
		if (save_existing_var(list, equality, data) == FAILURE)
			return (save_new_var(list, equality, data));
	}
	if (*list == NULL)
	{
		*list = ft_varnew(ft_strdup(equality[0]), ft_strdup(equality[1]));
		ft_free_char_pp(equality);
		if (*list == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
	}
	return (SUCCESS);
}

int	ft_search_for_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '=')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	save_variables(t_data *data, t_input_var *info, int i)
{
	char	**equality;

	while (info->first_line_split[i] != NULL)
	{
		if (ft_search_for_equal(info->first_line_split[i]) == SUCCESS)
		{
			equality = ft_split_var(info->first_line_split_ref[i], '=');
			if (equality == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
			equality[1] = expand_var(data, equality[1]);
			if (equality[1] == NULL)
			{
				ft_free_char_pp(equality);
				return (MALLOC_ERROR);
			}
			//sacar comillas
			equality[1] = ft_remove_quotes_var(equality);
			modify_exp_and_env(data, equality[0], equality[1]);
			save_var_info(data, equality, &data->var);
			if (refresh_home_var(data) != SUCCESS)
				return (MALLOC_ERROR);
			if (data->fatal_error == true)
				return (MALLOC_ERROR);
		}
		i++;
	}
	return (exit_codes(EXIT_0, data));
}

int	delete_head_var(t_var *vars, t_var *temp_var, t_var **list)
{
	temp_var = vars->next;
	if (temp_var->content != NULL)
		free(temp_var->content);
	if (temp_var->var != NULL)
		free(temp_var->var);
	free(vars);
	*list = temp_var;
	return (SUCCESS);
}

int	delete_middle_var(t_var *vars, t_var *temp_var)
{
	temp_var = vars->next;
	vars->next = vars->next->next;
	if (temp_var->content != NULL)
		free(temp_var->content);
	if (temp_var->var != NULL)
		free(temp_var->var);
	free(temp_var);
	return (SUCCESS);
}
