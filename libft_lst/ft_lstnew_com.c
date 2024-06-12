/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_com.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:16 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/07 13:42:25 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst_com.h"

t_command	*ft_lstnew_com(char **content)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!(new_node))
		return (NULL);
	new_node[0].content = content;
	new_node[0].next = NULL;
	return (new_node);
}

/* int	main(void)
{
	char	*data = "hola";
	t_list *node;

	node = ft_lstnew(data);
	if (node != NULL)
	{
		printf("Content of the node: %s\n", (node[0].content));
		free(node);
	}
	else
		printf("Node creation failed!\n");

	return (0);
} */
