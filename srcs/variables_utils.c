/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables _utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:08:35 by farah             #+#    #+#             */
/*   Updated: 2024/07/03 13:32:03 by ffauth-p         ###   ########.fr       */
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
