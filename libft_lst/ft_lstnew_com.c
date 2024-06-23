/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_com.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:16 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/20 20:56:30 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst_com.h"

t_command	*ft_lstnew_com(char **content)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!(new_node))
		return (NULL);
	new_node->content = content;
	new_node->full_path = NULL;
	new_node->text_input = NULL;
	new_node->redirect_input = NULL;
	new_node->redirect_output = NULL;
	new_node->fd_in = STDIN_FILENO;
	new_node->fd_out = STDOUT_FILENO;
	new_node->file_input = true;
	new_node->append_output = false;
	new_node->no_permissions = false;
	new_node->no_infile = false;
	new_node->temp_file = NULL;
	new_node->next = NULL;
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
