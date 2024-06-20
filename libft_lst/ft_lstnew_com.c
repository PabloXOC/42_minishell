/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_com.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:16 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/19 14:00:21 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst_com.h"

t_command	*ft_lstnew_com(char **content, char *full_path)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!(new_node))
		return (NULL);
	new_node->content = content;
	new_node->full_path = full_path;
	new_node->next = NULL;
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
