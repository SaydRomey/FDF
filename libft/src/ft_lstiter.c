/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:28:40 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/22 19:40:16 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
Iterates the list 'lst' 
and applies the function f to the content of each node
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_temp;

	lst_temp = lst;
	while (lst_temp)
	{
		f(lst_temp->content);
		lst_temp = lst_temp->next;
	}
}
