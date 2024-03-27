/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:25:20 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/08 17:01:14 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* void	*f(void *content)
{
	content = "hi";
	return (content);
}

void	del(void *content)
{
	content = NULL;
} */

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_list;
	void	*cont;

	new_list = NULL;
	while (lst != NULL)
	{
		cont = f(lst->content);
		new_node = ft_lstnew(cont);
		if (new_node == NULL)
		{
			free(cont);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

/* int	main(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	t_list	*new;

	node1 = ft_lstnew("node1");
	node2 = ft_lstnew("node2");
	node3 = ft_lstnew("node3");
	node1->next = node2;
	node2->next = node3;
	new = ft_lstmap(node1, f, del);
	printf("%s\n", new->content);
	printf("%s\n", new[0].next->content);
	printf("%s\n", new[0].next[0].next->content);
	printf("%s\n", new[0].next[0].next->next);
} */
