/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/09/19 18:32:11 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_export_list(t_data *data, char *var, char *cont)
{
	data->var_export = ft_varnew(ft_strdup(var), ft_strdup(cont));
	if (data->var_export == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	return (SUCCESS);
}

int	save_export_el(t_data *data, char *var, char *cont)
{
	t_var	*exp_lst;
	t_var	*temp_el;
	int		i;

	if (data->var_export == NULL)
		return (fill_export_list(data, var, cont));
	exp_lst = data->var_export;
	temp_el = ft_varnew(ft_strdup(var), ft_strdup(cont));
	if (ft_strncmp(var, exp_lst->var, ft_strlen(var) + 1) < 0)
	{
		ft_varadd_front(&data->var_export, temp_el);
		return (SUCCESS);
	}
	while (exp_lst->next != NULL)
	{
		if (ft_strncmp(var, exp_lst->next->var, ft_strlen(var) + 1) < 0)
		{
			ft_varadd_middle(&exp_lst, temp_el);
			return (SUCCESS);
		}
		exp_lst = exp_lst->next;
	}
	ft_varadd_back(&data->var_export, temp_el);
	return (SUCCESS);
}

void	modify_export(t_data *data, char *var, char *new_cont)
{
	t_var	*node;

	node = data->var_export;
	while (node != NULL)
	{
		if (ft_strncmp(var, node->var, ft_strlen(var) + 1) == 0)
		{
			free(node->content);
			node->content = ft_strdup(new_cont);
			return ;
		}
		node = node->next;
	}
	save_export_el(data, var, new_cont);
	refresh_home_var(data);
	return ;
}

bool	ft_export_isspecial(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i] != '=' && str[i] != 0)
	{
		if (ft_isalnum_bool(str[i]) == false && str[i] != '_')
			return (true);
		i++;
	}
	return (false);
}

bool	check_if_we_save_export_var(t_data *data, char *var)
{
	if (ft_export_isspecial(var) == true)
		return (false);
	else if (ft_starts_with_number(var) == true)
		return (false);
	else if (ft_strncmp(var, "\0", 1) == 0)
		return (false);
	return (true);
}
