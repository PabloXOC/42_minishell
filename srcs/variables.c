/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/07/06 16:53:07 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	safe_existing_var(t_var **list, char **equality, t_data *data)
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
		if (safe_existing_var(list, equality, data) == FAILURE)
			return (safe_new_var(list, equality, data));
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

int	save_variables(t_data *data, int i)
{
	char	**equality;

	while (data->input_info->first_line_split[i] != NULL)
	{
		if (ft_strrchr(data->input_info->first_line_split[i], '=') != NULL)
		{
			equality = ft_split(data->input_info->first_line_split[i], '=');
			if (equality == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
			equality[1] = expand_var(data, equality[1]);
			if (equality[1] == NULL)
			{
				ft_free_char_pp(equality);
				return (MALLOC_ERROR);
			}
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
