/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/06/15 20:37:21 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*ft_varnew(char *var, char *content)
{
	t_var	*new_node;

	new_node = (t_var *)malloc(sizeof(t_var));
	if (!(new_node))
		return (NULL);
	new_node[0].var = var;
	new_node[0].content = content;
	new_node[0].next = NULL;
	return (new_node);
}

int	ft_varsize(t_var *var)
{
	int	size;

	size = 0;
	while (var != NULL)
	{
		var = var->next;
		size++;
	}
	return (size);
}

t_var	*ft_varlast(t_var *var)
{
	int		size;
	int		i;

	size = ft_varsize(var);
	i = 0;
	while (i < size - 1)
	{
		var = var->next;
		i++;
	}
	return (var);
}

void	ft_varadd_back(t_var **var, t_var *new)
{
	t_var	*last_item;

	if (var != NULL && new != NULL)
	{
		last_item = ft_varlast(*var);
		if (last_item == NULL)
			*var = new;
		else
			last_item->next = new;
	}
}

void	ft_vardelone(t_var *var)
{
	if (var != NULL)
	{
		if (var->content != NULL)
			free(var->content);
		if (var->var != NULL)
			free(var->var);
	}
	free(var);
}

/* int	safe_new_var(t_command *command, char **equality)
{
	t_var	*var;

	var = ft_varnew(ft_strdup(equality[0]), ft_strdup(equality[1]));
	ft_free_char_pp(equality);
	if (var == NULL)
		return (MALLOC_ERROR);
	ft_varadd_back(&command->var, var);
	return (SUCCESS);
} */

int	safe_existing_var(t_data *data, char **equality)
{
	t_var	*temp_var;

	temp_var = data->var;
	while (temp_var != NULL)
	{
		if (strncmp(temp_var->var, equality[0], ft_strlen(equality[0])) == 0)
		{
			free(temp_var->content);
			temp_var->content = ft_strdup(equality[1]);
			if (temp_var->content == NULL)
				return (MALLOC_ERROR);
			ft_free_char_pp(equality);
			return (SUCCESS);
		}
		temp_var = temp_var->next;
	}
	return (FAILURE);
}

int	save_variables(t_data *data)
{
	char	**equality;
	int		i;

	i = 0;
	while (data->input_info->first_line_split[i] != NULL)
	{
		if (ft_strrchr(data->input_info->first_line_split[i], '=') != NULL)
		{
			equality = ft_split(data->input_info->first_line_split[i], '=');
			if (equality == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
			if (data->var == NULL)
			{
				data->var = ft_varnew(ft_strdup(equality[0]), ft_strdup(equality[1]));
				ft_free_char_pp(equality);
				if (data->var == NULL)
					return (ft_write_error_i(MALLOC_ERROR, data));
			}
			else
			{
				if (safe_existing_var(data, equality) == FAILURE)
				{
					if (safe_existing_var(data, equality) == MALLOC_ERROR)
						return (MALLOC_ERROR);
				}
			}
		}
	}
	return (SUCCESS);
}

int	delete_var(t_data *data, char *var_to_del)
{
	t_var	*vars;
	t_var	*temp_var;

	vars = data->var;
	while (vars->next != NULL)
	{
		if (vars->next->content != NULL && vars->next->var != NULL)
		{
			if (ft_strncmp(vars->next->var, var_to_del, ft_strlen(var_to_del)) == 0)
			{
				temp_var = vars->next;
				vars->next = vars->next->next;
				free(temp_var->content);
				free(temp_var->var);
				free(temp_var);
				return (SUCCESS);
			}
		}
		vars = vars->next;
	}
	return (SUCCESS);
}
