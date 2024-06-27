/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/06/27 16:47:08 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_vars(t_data *data)
{
	
}

char	*return_content_var(t_data *data, char *text, int len_v)
{
	t_var	*node;

	node = data->var;
	while (node != NULL)
	{
		if (ft_strncmp(text, node->var, len_v) == 0)
			return (node->content);
		node = node->next;
	}
	return (NULL);
}

int	len_var(char *str)
{
	int	i;

	i = 1;
	while (str[i] != 0)
	{
		if (ft_isdigit(str[i]) == 1 && i == 1)
			return (i);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (i - 1);
		i++;
	}
	return (i - 1);
}

char	*expand_var(t_data *data, char *text)
{
	t_var	*node;
	int		i;
	int		len_v;
	int		cont_v;

	while (text[i] != 0)
	{
		if (text[i] == '$')
		{	
			len_v = len_var(&text[i]);
			if (len_v = 0)
				return (NULL);
			cont_v = return_content_var(data, &text[i], len_v);
			ft_printf("len var: %d\n", len_v);
		}
		i++;
	}
	return (text);
	/* node = data->env_lst;
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
	node = ft_varnew(ft_strdup(var), ft_strdup(new_cont));
	ft_varadd_back(&data->env_lst, node);
	return ; */
}
