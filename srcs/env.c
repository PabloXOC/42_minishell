/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/07/05 11:28:34 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*find_env_el(t_data *data, char *name)
{
	t_var	*node;

	node = data->env_lst;
	while (node != NULL)
	{
		if (ft_strncmp(name, node->var, ft_strlen(name) + 1) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

char	*return_content_var(t_var *var_list, char *text)
{
	t_var	*node;

	node = var_list;
	while (node != NULL)
	{
		if (ft_strncmp(text, node->var, ft_strlen(text) + 1) == 0)
			return (node->content);
		node = node->next;
	}
	return (NULL);
}

void	modify_env(t_data *data, char *var, char *new_cont)
{
	t_var	*node;

	node = data->env_lst;
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
	return ;
}

int	print_env(t_data *data)
{
	t_var	*node;

	node = data->env_lst;
	while (node != NULL)
	{
		ft_printf("%s=%s\n", node->var, node->content);
		node = node->next;
	}
	exit_codes(EXIT_0, data);
	return (SUCCESS);
}

t_var	*safe_env(char **env)
{
	int		i;
	t_var	*head;
	t_var	*node;
	char	**el;

	if (env == NULL)
		return (NULL);
	el = ft_split(env[0], '=');
	head = ft_varnew(ft_strdup(el[0]), ft_strdup(el[1]));
	ft_free_char_pp(el);
	i = 1;
	while (env[i] != NULL)
	{
		el = ft_split(env[i], '=');
		node = ft_varnew(ft_strdup(el[0]), ft_strdup(getenv(el[0])));
		ft_varadd_back(&head, node);
		ft_free_char_pp(el);
		i++;
	}
	return (head);
}
