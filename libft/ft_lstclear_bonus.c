/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:25:20 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/07 15:56:00 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* void	del(void *content)
{
	free(content);
} */

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*int_list;

	while (*lst != NULL)
	{
		int_list = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = int_list;
	}
}

/* int	main(void)
{
	char	*data = "hola";
	t_list	*node;
	t_list	*new_f;
	t_list	*new_e;

	node = ft_lstnew(data);
	new_f = ft_lstnew("mynamepablo");
	new_e = ft_lstnew("vivaespana");
	if (node != NULL)
	{
		printf("Content of the node: %s\n", (node[0].content));
		free(node);
	}
	else
		printf("Node creation failed!\n");
	ft_lstadd_front(&node, new_f);
	printf("%s\n", node[0].next[0].content);
	printf("%d\n", ft_lstsize(node));
	ft_lstadd_back(&node, new_e);
	printf("%s\n", (ft_lstlast(node))[0].content);
	printf("%s\n", node[0].content);
	ft_lstdelone(node, del);
	printf("%s\n", node[0].content);
	return (0);
} */
