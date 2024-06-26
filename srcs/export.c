/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/06/26 18:22:32 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_var(t_data *data, t_command *full_com, t_var **list)
{
	char	**equality;
	t_var 	*temp_var;
	int		i;

	i = 1;
	while (full_com->content[i] != NULL)
	{
		equality = ft_split(full_com->content[1], '=');
		if (equality == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		if (*list != NULL)
		{
			if (safe_existing_var(list, equality) == FAILURE)
			{
				temp_var = ft_varnew(ft_strdup(equality[0]), ft_strdup(equality[1]));
				if (temp_var == NULL)
					return (MALLOC_ERROR);
				ft_varadd_back(list, temp_var);
			}
		}
		if (*list == NULL)
		{
			*list = ft_varnew(ft_strdup(equality[0]), ft_strdup(equality[1]));
			ft_free_char_pp(equality);
			if (*list == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
		}
		i++;
	}
	print_vars(*list);
	return (SUCCESS);
}
