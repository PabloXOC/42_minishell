/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/11/05 17:33:54 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free(var);
	}
}

void	ft_varsclear(t_var **var)
{
	t_var	*temp;
	int		i;

	i = 0;
	while (*var != NULL)
	{
		temp = (*var)->next;
		ft_vardelone(*var);
		*var = temp;
		i++;
	}
}

int	save_new_var(t_var **list, char **equality, t_data *data)
{
	t_var	*temp_var;

	temp_var = ft_varnew(ft_strdup(equality[0]), ft_strdup(equality[1]));
	ft_free_char_pp(equality);
	if (temp_var == NULL)
		return (error_i(MALLOC_ERROR, data));
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
