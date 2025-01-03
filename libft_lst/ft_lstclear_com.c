/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_com.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:25:20 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/20 15:26:41 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst_com.h"

/* void	del(void *content)
{
	free(content);
} */

void	ft_lstclear_com(t_command **lst, void (*del)(char **))
{
	t_command	*com_list;

	while (*lst != NULL)
	{
		com_list = (*lst)->next;
		ft_lstdelone_com(*lst, del);
		*lst = com_list;
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
