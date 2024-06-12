/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_com.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:16 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/07 13:42:21 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst_com.h"

int	ft_lstsize_com(t_command *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

/* int	main(void)
{
	char	*data = "hola";
	t_list	*node;
	t_list	*new;

	new = ft_lstnew("mynamepablo");
	node = ft_lstnew(data);
	if (node != NULL)
	{
		printf("Content of the node: %s\n", (node[0].content));
		free(node);
	}
	else
		printf("Node creation failed!\n");
	ft_lstadd_front(&node, new);
	printf("%s\n", node[0].next[0].content);
	printf("%d\n", ft_lstsize(node));
	return (0);
} */
