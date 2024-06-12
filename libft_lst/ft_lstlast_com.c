/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_com.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:16 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/07 13:42:36 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst_com.h"

t_command	*ft_lstlast_com(t_command *lst)
{
	int		size;
	int		i;

	size = ft_lstsize_com(lst);
	i = 0;
	while (i < size - 1)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
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
	node = ft_lstlast(node);
	printf("%d\n", ft_lstsize(node));
	return (0);
} */
