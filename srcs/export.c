/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/09/21 14:28:39 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_equality(char **equality, t_data *data)
{
	char	**new_eq;

	new_eq = (char **)malloc(3 * sizeof(char *));
	if (new_eq == NULL)
	{
		ft_free_char_pp(equality);
		return ((char **) error_c(MALLOC_ERROR,
				data, data->spec[data->sc_n]));
	}
	new_eq[2] = NULL;
	new_eq[0] = ft_strdup(equality[0]);
	new_eq[1] = ft_strdup("");
	if (new_eq[0] == NULL || new_eq[1] == NULL)
	{
		ft_free_char_pp(equality);
		return ((char **) error_c(MALLOC_ERROR,
				data, data->spec[data->sc_n]));
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
			return (error_i(MALLOC_ERROR, data));
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
