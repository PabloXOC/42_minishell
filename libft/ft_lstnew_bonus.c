/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:16 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/29 15:18:42 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void **content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
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
