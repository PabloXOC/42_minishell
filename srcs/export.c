/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/06/27 12:12:53 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_export_el(t_data *data, char *var, char *cont)
{
	t_var 	*exp_lst;
	t_var	*temp_el;
	int		i;

	if (data->var_export == NULL)
	{	
		data->var_export = ft_varnew(ft_strdup(var), ft_strdup(cont));
		if (data->var_export == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		return (SUCCESS);
	}
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
	t_var 	*temp_var;
	int		i;

	i = 1;
	while (full_com->content[i] != NULL)
	{
		equality = ft_split(full_com->content[i], '=');
		if (equality == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		save_var_info(data, equality, list);
		equality = ft_split(full_com->content[i], '=');
		if (equality == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		save_export_el(data, equality[0], equality[1]);
		i++;
	}
	print_vars(*list);
	print_vars(data->var_export);
	return (SUCCESS);
}

void	export_list(t_data *data)
{
	t_var	*env_list;

	env_list = data->env_lst;
	while(env_list != NULL)
	{
		save_export_el(data, env_list->var, env_list->content);
		env_list = env_list->next;
	}
}

void	print_export(t_data *data)
{
	t_var	*node;

	node = data->var_export;
	while (node != NULL)
	{
		ft_printf("declare -x %s=\"%s\"\n", node->var, node->content);
		node = node->next;
	}
}
