/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/09/27 14:02:42 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (exit_codes(EXIT_0, data));
}

int	save_env2(char **env, t_var **head, char **el)
{
	int		i;
	t_var	*node;

	i = 1;
	while (env[i] != NULL)
	{
		el = ft_split(env[i], '=');
		if (el == NULL)
			return (MALLOC_ERROR);
		node = ft_varnew(ft_strdup(el[0]), ft_strdup(getenv(el[0])));
		if (node == NULL)
		{
			ft_free_char_pp(el);
			return (MALLOC_ERROR);
		}
		ft_varadd_back(head, node);
		ft_free_char_pp(el);
		i++;
	}
	return (SUCCESS);
}

t_var	*save_env(char **env)
{
	t_var	*head;
	char	**el;

	if (env == NULL)
		return (NULL);
	el = ft_split(env[0], '=');
	if (el == NULL)
		return (NULL);
	head = ft_varnew(ft_strdup(el[0]), ft_strdup(el[1]));
	if (head == NULL)
	{
		ft_free_char_pp(el);
		return (NULL);
	}
	ft_free_char_pp(el);
	if (save_env2(env, &head, el) == MALLOC_ERROR)
		return (NULL);
	return (head);
}
