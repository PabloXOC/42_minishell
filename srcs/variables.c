/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/04/30 14:02:03 by farah            ###   ########.fr       */
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

int	safe_var(t_command *command)
{
	char	**equality;
	t_var	*var;

	if (command->create_var != NULL)
	{
		equality = ft_split(command->create_var, '=');
		if (equality == NULL)
			return (MALLOC_ERROR);
		var = ft_varnew(ft_strdup(equality[0]), ft_strdup(equality[1]));
		ft_free_char_pp(equality);
		if (var == NULL)
			return (MALLOC_ERROR);
		if (command->var == NULL)
			command->var = var;
		else
			ft_varadd_back(&command->var, var);
	}
	return (SUCCESS);
}

int	delete_var(t_command *command, char *var_to_del)
{
	t_var	*vars;

	vars = command->var;
	while (vars != NULL)
	{
		if (vars->content != NULL && vars->var != NULL)
		{
			if (ft_strncmp(vars->var, var_to_del, ft_strlen(var_to_del)) == 0)
			{
				free(vars->content);
				free(vars->var);
				vars->content = NULL;
				vars->var = NULL;
				return (SUCCESS);
			}
		}
		vars = vars->next;
	}
	return (SUCCESS);
}
