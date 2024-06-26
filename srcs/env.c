/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/06/26 12:50:35 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_data *data)
{
	t_var	*node;

	node = data->env_lst;
	while (node != NULL)
	{
		ft_printf("%s=%s\n", node->var, node->content);
		node = node->next;
	}
}

t_var	*safe_env(char **env)
{
	int	i;
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
		node = ft_varnew(ft_strdup(el[0]), getenv(el[0]));
		ft_varadd_back(&head, node);
		ft_free_char_pp(el);
		i++;
	}
	return (head);
}