/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/09/04 19:37:16 by paxoc01          ###   ########.fr       */
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

char	**new_equality(char **equality, t_data *data)
{
	char	**new_eq;
	new_eq = (char **)malloc(3 * sizeof(char *));
	if (new_eq == NULL)
	{
		ft_free_char_pp(equality);
		return ((char **) ft_write_error_c(MALLOC_ERROR, data, data->specific[data->sc_pos]));
	}
	new_eq[2] = NULL;
	new_eq[0] = ft_strdup(equality[0]);
	new_eq[1] = ft_strdup("");
	if (new_eq[0] == NULL || new_eq[1] == NULL)
	{
		ft_free_char_pp(equality);
		return ((char **) ft_write_error_c(MALLOC_ERROR, data, data->specific[data->sc_pos]));
	}
	ft_free_char_pp(equality);
	return (new_eq);
}

int	export_var(t_data *data, t_command *full_com, t_var **list, int i)
{
	char	**equality;
	t_var	*temp_var;

	if (ft_strrchr(full_com->content[i], '=') != NULL)
	{
		equality = ft_split(full_com->content[i], '=');
		if (equality == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		if (equality[1] == NULL)
			equality = new_equality(equality, data);
		modify_export(data, equality[0], equality[1]);
		modify_env(data, equality[0], equality[1]);
		save_var_info(data, equality, list);
	}
	else
	{
		if (return_content_var(data->var_export, full_com->content[i]) == NULL)
		{
			save_export_el(data, full_com->content[i], "");
			refresh_home_var(data);
		}
	}
	return (SUCCESS);
}

int	export(t_data *data, t_command *full_com, t_var **list, int i)
{
	bool	error;
	int		exit_code;

	error = false;
	while (full_com->content[i] != NULL)
	{
		if (check_if_we_save_export_var(data, full_com->content[i]) == true)
			export_var(data, full_com, list, i);
		else
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(full_com->content[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			error = true;
			exit_code = exit_codes(EXIT_2, data);
		}
		i++;
	}
	if (error == false)
		exit_code = exit_codes(EXIT_0, data);
	return (exit_code);
}

int	print_export(t_data *data)
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
	return (exit_codes(EXIT_0, data));
}
