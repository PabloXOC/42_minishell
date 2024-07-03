/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/07/03 09:58:45 by farah            ###   ########.fr       */
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

void	ft_varadd_front(t_var **lst, t_var *new)
{
	if (lst != NULL && new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
	return ;
}

void	ft_varadd_middle(t_var **lst, t_var *new)
{
	t_var	*next;

	if (lst != NULL && new != NULL)
	{
		next = (*lst)->next;
		(*lst)->next = new;
		new->next = next;
	}
	return ;
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

void	ft_varsclear(t_var **var)
{
	t_var	*temp;

	while (*var != NULL)
	{
		temp = (*var)->next;
		ft_vardelone(*var);
		*var = temp;
	}
}

int	safe_new_var(t_var **list, char **equality, t_data *data)
{
	t_var	*temp_var;

	temp_var = ft_varnew(ft_strdup(equality[0]), ft_strdup(equality[1]));
	ft_free_char_pp(equality);
	if (temp_var == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	ft_varadd_back(list, temp_var);
	return (SUCCESS);
}

void	print_vars(t_var *list)
{
	t_var	*var;

	var = list;
	while (var != NULL)
	{
		ft_printf("%s = %s\n", var->var, var->content);
		var = var->next;
	}
}

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
			equality[1] = expand_var(data, equality[1]);
			if (equality[1] == NULL)
			{
				ft_free_char_pp(equality);
				return (MALLOC_ERROR);
			}
			save_var_info(data, equality, &data->var);
			if (data->fatal_error == true)
				return (MALLOC_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

static int	delete_head_var(t_var *vars, t_var *temp_var, t_var **list)
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

static int	delete_middle_var(t_var *vars, t_var *temp_var)
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
