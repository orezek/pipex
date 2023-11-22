/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:38:48 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:59:43 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*current;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current->next != NULL)
	{
		temp = current;
		current = current->next;
		del(temp->content);
		free(temp);
	}
	del(current->content);
	free(current);
	*lst = NULL;
}
