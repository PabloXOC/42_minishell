/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:16 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/07 13:03:49 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		size;
	int		i;

	size = ft_lstsize(lst);
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
