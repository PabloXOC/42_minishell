/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:25:20 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/07 13:08:25 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_item;

	if (lst != NULL && new != NULL)
	{
		last_item = ft_lstlast(*lst);
		if (last_item == NULL)
			*lst = new;
		else
			last_item->next = new;
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
	return (0);
} */
