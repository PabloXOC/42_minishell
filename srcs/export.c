/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/07/02 17:40:24 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_export_list(t_data *data, char *var, char *cont)
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
	return ;
}

int	export_var(t_data *data, t_command *full_com, t_var **list)
{
	char	**equality;
	t_var	*temp_var;
	int		i;

	i = 1;
	while (full_com->content[i] != NULL)
	{
		if (ft_strrchr(full_com->content[i], '=') != NULL)
		{
			equality = ft_split(full_com->content[i], '=');
			if (equality == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
			if (equality[1] == NULL)
				equality[1] = ft_strdup("");
			if (equality[1] == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
			modify_export(data, equality[0], equality[1]);
			modify_env(data, equality[0], equality[1]);
			save_var_info(data, equality, list);
		}
		else
			modify_export(data, full_com->content[i], NULL);
		i++;
	}
	return (SUCCESS);
}

void	print_export(t_data *data)
{
	t_var	*node;

	node = data->var_export;
	while (node != NULL)
	{
		if (find_env_el(data, node->var) != NULL)
			ft_printf("declare -x %s=\"%s\"\n", node->var, node->content);
		else
			ft_printf("declare -x %s\n", node->var, node->content);
		node = node->next;
	}
}
