/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_com.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:25:20 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/07 13:43:12 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst_com.h"

void	ft_lstadd_back_com(t_command **lst, t_command *new)
{
	t_command	*last_item;

	if (lst != NULL && new != NULL)
	{
		last_item = ft_lstlast_com(*lst);
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
