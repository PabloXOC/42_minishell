/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_com.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:25:20 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/19 17:00:00 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst_com.h"

/* void	*f(void *content)
{
	content = "hi";
	return (content);
}

void	del(void *content)
{
	content = NULL;
} */

/* t_command	*ft_lstmap_com(t_command *lst, void *(*f)(void *), void (*del)(char **))
{
	t_command	*new_node;
	t_command	*new_list;
	void	*cont;

	new_list = NULL;
	while (lst != NULL)
	{
		cont = f(lst->content);
		new_node = ft_lstnew_com(cont);
		if (new_node == NULL)
		{
			free(cont);
			ft_lstclear_com(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back_com(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
} */

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
